class pNetMessage;
class pNetMessagePack;
class pNetworkClient;
class pNetworkServer;

class pNetMessage
{
friend pNetMessagePack;

	protected:
		unsigned short msg;
		unsigned short len;
		char *data;
		bool local_data;

	public:
		pNetMessage();
		virtual ~pNetMessage();
		
		pNetMessage(const pNetMessage& in);
		void operator=(const pNetMessage& in);
		
		pNetMessage(unsigned short msg,unsigned short size,const void *buf,bool local_data=false);
		set_message(unsigned short msg,unsigned short size,const void *buf,bool local_data=false);

		unsigned short get_len() const
		{ return len; }
		unsigned short get_msg() const
		{ return msg; }
		const char *get_data() const
		{ return data; };
};

class pNetMessagePack
{
friend pNetworkClient;
friend pNetworkServer;

	protected:
		unsigned int size;
		unsigned short num;
		unsigned short *msg;
		unsigned short *len;
		unsigned int *pos;
		char *data;
		int extra_data;

	public:
		pNetMessagePack();
		virtual ~pNetMessagePack();
		
		pNetMessagePack(const pNetMessagePack& in);
		void operator=(const pNetMessagePack& in);

		void reset();
		void allocate(unsigned int size_,unsigned short num_);
		const char *get_send_buffer(unsigned int& size);

		bool add_message(const pNetMessage& m);
		bool get_message(int i,pNetMessage& m);
		
		unsigned short get_message_count()
		{ return num; }

		unsigned short get_size() const
		{ return size; }
		const char *get_data() const
		{ return data; };
};

class pNetworkClient
{
	protected:
		TCPsocket sock;
		
		pString server;
		unsigned short port;

		IPaddress ip;

		bool read(void *data,int size);

	public:
		pNetworkClient();
		virtual ~pNetworkClient();
		
		pNetworkClient(const char *server_,unsigned short port_);
		set_server(const char *server_,unsigned short port_);
		
		bool connect();
		void disconnect();
		bool is_connected();

		int get_message(pNetMessagePack& mp);
		bool send_message(pNetMessagePack& mp);
};

class pNetworkServer
{
	protected:
		TCPsocket sock;
		pArray<TCPsocket> clients;
		
		pString server;
		unsigned short port;

		IPaddress ip;

		bool read(TCPsocket client,void *data,int size);
		int receive_message(TCPsocket client,pNetMessagePack& m);

	public:
		pNetworkServer();
		~pNetworkServer();

		pNetworkServer(unsigned short port_);
		set_port(unsigned short port_);

		bool create();
		void destroy();
		bool is_created();

		int get_message(pNetMessagePack& mp,int& client,pArray<int> *dropclients=0);
		bool send_message(pNetMessagePack& mp,int client,pArray<int> *dropclients=0);

		bool get_client_info(int client,pString& info);
		bool get_server_info(pString& info);

		int get_client_count()
		{ return clients.num; };
		bool drop_client(int client);
};

class pSocketSet
{
	protected:
		SDLNet_SocketSet set;

	public:
		pSocketSet(int num);
		~pSocketSet();

		void add(TCPsocket sock);
		int activity();
};
