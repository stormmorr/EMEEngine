#include "pch.h"
#include "paralelo3d.h"

#ifdef P_NETWORK

/////// pNetMessage ///////

pNetMessage::pNetMessage() :
	msg(0),
	len(0),
	data(0),
	local_data(false)
{
}

pNetMessage::~pNetMessage()
{
	if (local_data)
		delete data;
}

pNetMessage::pNetMessage(const pNetMessage& in)
{
	msg=in.msg;
	len=in.len;
	local_data=in.local_data;

	if (local_data)
	{
		data=new char[len];
		memcpy(data,in.data,len);
	}
	else
		data=in.data;		
}

void pNetMessage::operator=(const pNetMessage& in)
{
	if (local_data)
		delete data;

	msg=in.msg;
	len=in.len;
	local_data=in.local_data;

	if (local_data)
	{
		data=new char[len];
		memcpy(data,in.data,len);
	}
	else
		data=in.data;		
}
	
pNetMessage::pNetMessage(unsigned short msg_,unsigned short len_,const void *data_,bool local_data_)
{
	msg=msg_;
	len=len_;
	local_data=local_data_;
	
	if (local_data)
	{
		data=new char[len];
		memcpy(data,data_,len);
	}
	else
		data=(char *)data_;
}

pNetMessage::set_message(unsigned short msg_,unsigned short len_,const void *data_,bool local_data_)
{
	if (local_data)
		delete data;

	msg=msg_;
	len=len_;
	local_data=local_data_;
	
	if (local_data)
	{
		data=new char[len];
		memcpy(data,data_,len);
	}
	else
		data=(char *)data_;
}

/////// pNetMessagePack ///////

pNetMessagePack::pNetMessagePack() :
	size(0),
	num(0),
	msg(0),
	len(0),
	pos(0),
	data(0),
	extra_data(0)
{
}

pNetMessagePack::~pNetMessagePack()
{
	reset();
}

pNetMessagePack::pNetMessagePack(const pNetMessagePack& in)
{
	size=in.size;
	num=in.num;
	extra_data=in.extra_data;
	if (num)
	{
		msg=new unsigned short[num];
		len=new unsigned short[num];
		pos=new unsigned int[num];
		data=new char[size+extra_data];
		data+=extra_data;

		for( int i=0;i<num;i++ )
		{
			msg[i]=in.msg[i];
			len[i]=in.len[i];
			pos[i]=in.pos[i];
		}
		memcpy(data,in.data,size);
	}
	else
	{
		msg=0;
		len=0;
		pos=0;
		data=0;
	}
}

void pNetMessagePack::operator=(const pNetMessagePack& in)
{
	reset();

	size=in.size;
	num=in.num;
	extra_data=in.extra_data;
	if (num)
	{
		msg=new unsigned short[num];
		len=new unsigned short[num];
		pos=new unsigned int[num];
		data=new char[size+extra_data];
		data+=extra_data;

		for( int i=0;i<num;i++ )
		{
			msg[i]=in.msg[i];
			len[i]=in.len[i];
			pos[i]=in.pos[i];
		}
		memcpy(data,in.data,size);
	}
	else
	{
		msg=0;
		len=0;
		pos=0;
		data=0;
	}
}

void pNetMessagePack::reset()
{
	delete msg;
	delete len;
	delete pos;
	if (data)
		delete (data-extra_data);

	msg=0;
	len=0;
	pos=0;
	data=0;

	size=0;
	num=0;
	extra_data=0;
}


void pNetMessagePack::allocate(unsigned int size_,unsigned short num_)
{
	reset();

	size=size_;
	num=num_;

	extra_data=sizeof(unsigned int)+sizeof(unsigned short)+2*num*sizeof(unsigned short);

	msg=new unsigned short[num];
	len=new unsigned short[num];
	pos=new unsigned int[num];
	data=new char[size+extra_data];
	data+=extra_data;
}

bool pNetMessagePack::add_message(const pNetMessage& m)
{
	unsigned short *tmp1;
	char *tmp2;
	unsigned int *tmp3;
	int i;
	
	tmp1=new unsigned short[num+1];
	if (msg)
		for( i=0;i<num;i++ )
			tmp1[i]=msg[i];
	delete msg;
	msg=tmp1;

	tmp1=new unsigned short[num+1];
	if (len)
		for( i=0;i<num;i++ )
			tmp1[i]=len[i];
	delete len;
	len=tmp1;

	tmp3=new unsigned int[num+1];
	if (pos)
		for( i=0;i<num;i++ )
			tmp3[i]=pos[i];
	delete pos;
	pos=tmp3;

	int ed=sizeof(unsigned int)+sizeof(unsigned short)+2*(num+1)*sizeof(unsigned short);

	tmp2=new char[size+m.len+ed];
	tmp2+=ed;
	if (data)
		memcpy(tmp2,data,size);
	if (data)
		delete (data-extra_data);
	data=tmp2;
	extra_data=ed;
	
	msg[num]=m.msg;
	len[num]=m.len;
	if (num)
		pos[num]=size;
	else
		pos[num]=0;
	memcpy(&data[size],m.data,m.len);
	
	num++;
	size+=m.len;

	return true;
}

bool pNetMessagePack::get_message(int i,pNetMessage& m)
{
	if (i<0 || i>=num)
		return false;

	m.set_message(msg[i],len[i],&data[pos[i]],false);

	return true;
}

const char *pNetMessagePack::get_send_buffer(unsigned int& size_)
{
	if (data==0 || num==0)
		return 0;

	char *data_=data-extra_data;

	unsigned int *ui=(unsigned int *)data_;
	unsigned short *us=(unsigned short *)(data_+sizeof(unsigned int));
	
	int i;
	
	*ui=size;
	*us=num;
	us++;
	for( i=0;i<num;i++ )
		us[i]=msg[i];
	us+=num;
	for( i=0;i<num;i++ )
		us[i]=len[i];

	size_=size+extra_data;

	return data_;
}

/////// pNetworkClient ///////

pNetworkClient::pNetworkClient() :
	sock(0),
	port(0)
{
	ip.host=0;
	ip.port=0;
}

pNetworkClient::~pNetworkClient()
{
	if (is_connected())
		disconnect();
}

pNetworkClient::pNetworkClient(const char *server_,unsigned short port_)
{
	sock=0;

	server=server_;
	port=port_;

	ip.host=0;
	ip.port=0;
}

pNetworkClient::set_server(const char *server_,unsigned short port_)
{
	server=server_;
	port=port_;
}
	
bool pNetworkClient::connect()
{
	if (server.length()==0 || port==0)
		return false;

	if (SDLNet_ResolveHost(&ip,(const char *)server,port)==-1)
		return false;
	
	sock=SDLNet_TCP_Open(&ip);
	if (sock==0)
		return false;

	return true;
}

void pNetworkClient::disconnect()
{
	if (sock)
	{
		SDLNet_TCP_Close(sock);
		sock=0;
	}
}

bool pNetworkClient::is_connected()
{
	return sock!=0;
}

bool pNetworkClient::read(void *data,int size)
{
	int i=0,r;
	while(i<size)
	{
		r=SDLNet_TCP_Recv(sock,&((char *)data)[i],size-i);
		if (r<0)
			return false;
		i+=r;
	}
	return true;
}

int pNetworkClient::get_message(pNetMessagePack& mp)
{
	pSocketSet set(1);
	set.add(sock);
	int i=set.activity();
	if (i<=0)
		return i;

	if (SDLNet_SocketReady(sock)==0)
		return 0;

	unsigned int size;
	unsigned short num;

	if (read(&size,sizeof(unsigned int))==false)
		return -1;
	if (read(&num,sizeof(unsigned short))==false)
		return -1;

	if (num==0)
		return 0;
	mp.allocate(size,num);

	if (read(mp.msg,sizeof(unsigned short)*num)==false)
		return -1;
	if (read(mp.len,sizeof(unsigned short)*num)==false)
		return -1;

	if (read(mp.data,size)==false)
		return -1;

	mp.pos[0]=0;
	for( i=1;i<num;i++ )
		mp.pos[i]=mp.pos[i-1]+mp.len[i-1];

	return 1;
}

bool pNetworkClient::send_message(pNetMessagePack& mp)
{
	if (sock==0)
		return false;

	const char *sendbuf;
	unsigned int size;

	sendbuf=mp.get_send_buffer(size);
	
	if (sendbuf==0)
		return false;
	
	int result=SDLNet_TCP_Send(sock,(void *)sendbuf,size);
	
	return result==size;
}

/////// pNetworkServer ///////

pNetworkServer::pNetworkServer() :
	sock(0),
	port(0)
{
	ip.host=0;
	ip.port=0;
}

pNetworkServer::~pNetworkServer()
{
	if (is_created())
		destroy();
}

pNetworkServer::pNetworkServer(unsigned short port_)
{
	sock=0;
	
	port=port_;

	ip.host=0;
	ip.port=0;
}

pNetworkServer::set_port(unsigned short port_)
{
	port=port_;
}

bool pNetworkServer::create()
{
	if(SDLNet_ResolveHost(&ip,NULL,port)==-1)
		return false;

	sock=SDLNet_TCP_Open(&ip);
	if(!sock)
		return false;

	return true;
}

void pNetworkServer::destroy()
{
	int i;
	for( i=0;i<clients.num;i++ )
		SDLNet_TCP_Close(clients.buf[i]);
	SDLNet_TCP_Close(sock);
	
	sock=0;
	server="";
	clients.free();
}

bool pNetworkServer::is_created()
{
	return sock!=0;
}

int pNetworkServer::get_message(pNetMessagePack& mp,int& client,pArray<int> *dropclients)
{
	int i,j;

	pSocketSet set(clients.num+1);
	set.add(sock);
	for( i=0;i<clients.num;i++ )
		set.add(clients.buf[i]);

	if (set.activity()<=0)
		return 0;

	if (dropclients)
		dropclients->clear();
	client=-1;

	for( i=0;i<clients.num;i++ )
	{
		if (SDLNet_SocketReady(clients.buf[i])==0)
			continue;

		j=receive_message(clients.buf[i],mp);
		if (j==1)
		{
			client=i;
			break;
		}
		else
		if (j==-1 && dropclients)
			dropclients->add(i);
	}

	if(SDLNet_SocketReady(sock))
	{
		TCPsocket newclient=SDLNet_TCP_Accept(sock);
		if (newclient)
			clients.add(newclient);
	}

	return client>-1;
}

bool pNetworkServer::read(TCPsocket client,void *data,int size)
{
	int i=0,r;
	while(i<size)
	{
		r=SDLNet_TCP_Recv(client,&((char *)data)[i],size-i);
		if (r<=0)
			return false;
		i+=r;
	}
	return true;
}

int pNetworkServer::receive_message(TCPsocket client,pNetMessagePack& mp)
{
	unsigned int size;
	unsigned short num;

	if (read(client,&size,sizeof(unsigned int))==false)
		return -1;
	if (read(client,&num,sizeof(unsigned short))==false)
		return -1;

	if (num==0)
		return 0;
	mp.allocate(size,num);

	if (read(client,mp.msg,sizeof(unsigned short)*num)==false)
		return -1;
	if (read(client,mp.len,sizeof(unsigned short)*num)==false)
		return -1;

	if (read(client,mp.data,size)==false)
		return -1;

	mp.pos[0]=0;
	for( int i=1;i<num;i++ )
		mp.pos[i]=mp.pos[i-1]+mp.len[i-1];

	return true;
}

bool pNetworkServer::send_message(pNetMessagePack& m,int client,pArray<int> *dropclients)
{
	if (client<-1 || client>=clients.num)
		return false;

	const char *sendbuf;
	unsigned int size;

	sendbuf=m.get_send_buffer(size);
	
	if (sendbuf==0)
		return false;

	if (dropclients)
		dropclients->clear();

	if (client==-1)
	{
		int i,j,result=0;
		for( i=0;i<clients.num;i++ )
		{
			j=SDLNet_TCP_Send(clients.buf[i],(void *)sendbuf,size);
			if (j==size)
				result++;
			else
				if (dropclients)
					dropclients->add(i);
		}
		
		return result==clients.num;
	}
	else
	{
		int result=SDLNet_TCP_Send(clients.buf[client],(void *)sendbuf,size);
		if (result==size)
			return true;
		if (dropclients)
			dropclients->add(client);
	}

	return false;
}

bool pNetworkServer::get_client_info(int client,pString& info)
{
	info="";

	if (client<0 || client>=clients.num)
		return false;

	IPaddress *clientip;

	clientip=SDLNet_TCP_GetPeerAddress(clients.buf[client]);
	if (clientip==0)
		return false;

	const char *host=SDLNet_ResolveIP(clientip);
	if (host)
		info=host;
	
	return true;
}

bool pNetworkServer::get_server_info(pString& info)
{
	info="";

	if (is_created()==false)
		return false;

	const char *host=SDLNet_ResolveIP(&ip);
	if (host)
		info=host;

	return true;
}

bool pNetworkServer::drop_client(int client)
{
	if (client<0 || client>=clients.num)
		return false;

	SDLNet_TCP_Close(clients.buf[client]);
	clients.remove(client);

	return true;
}

/////// pSocketSet ///////

pSocketSet::pSocketSet(int num)
{
	set=SDLNet_AllocSocketSet(num);
}

pSocketSet::~pSocketSet()
{
	SDLNet_FreeSocketSet(set);
}

void pSocketSet::add(TCPsocket sock)
{
	SDLNet_TCP_AddSocket(set,sock);
}

int pSocketSet::activity()
{
	int num=SDLNet_CheckSockets(set,0);
	if (num<0)
		return -1;
	return num;
}

#endif