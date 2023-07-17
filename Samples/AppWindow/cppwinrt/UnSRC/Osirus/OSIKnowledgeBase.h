/*
 * RebeccaAIML, Artificial Intelligence Markup Language 
 * C++ api and engine.
 *
 * Copyright (C) 2005 Frank Hassanabad
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

class myCallBacks : public CallBacks
{
	public:

		/**
		 * This is called for each AIML 
		 * "Gossip" tag.
		 *
		 * I am just printing out the gossip.
		 * You can do other things like store it 
		 * in a file and then reload the file at 
		 * startup as a type of persistance.
		 *
		 * \param gossip The gossip sent to be 
		 * stored as you see fit
		 */
		void storeGossip(const char * const gossip) 
		{ 
			cout << "[Gossip: " << gossip << " ]" << endl;
		}

		/**
		 * This is called for each AIML 
		 * category that is loaded into 
		 * memory.  
		 *
		 * Loadtime occurs whenver the call 
		 * GraphBuilder::createGraph() is made.
		 * For every 5000 categories loaded into
		 * Rebecca's internal data structure 
		 * this prints a output message about it.
		 */
		void categoryLoaded()
		{
			static int i = 0;
			const int numberOfCategories = 5000;
			
			/*
			 * Clever way to say if "i" is a multiple 
			 * of 5000 then print out the number of 
			 * categories loaded so far.
			 */
			if(++i % numberOfCategories == 0)
			{
				cout << "[" << i << " categories loaded]" << endl;
			}
		}

		/**
		 * Before each AIML file is parsed this method is called.
         *
		 * \param fileName The name of the file about to be parsed.
		 */
		void filePreLoad(const char *const fileName)
		{
			cout << "[Loading      " << fileName << "]" << endl;
		}
		
		/**
		 * After each AIML file is parsed, this method is called.
         *
		 * \param fileName The name of the file just parsed.
		 */
		void filePostLoad(const char *const fileName)
		{
			cout << "[Done loading " << fileName << "]" << endl;
		}

		/**
		 * When the "srai" AIML tag is called, the text 
		 * is sent to this method.
		 *
		 * Usually refered to as symbolic reduction, you 
		 * can see what text is being re-fed back into the 
		 * AIML GraphBuilder::getResponse() by AIML its self.
		 *
		 * \param symbol The text which is being sent back
		 * into GraphBuilder::getResponse().
		 */
		void symbolicReduction(const char *const symbol)
		{
			cout << "Symbolic reduction: " << symbol << endl;
		}

		/**
		 * A infinite symbolic reduction has occured and 
		 * has been terminated.
		 *
		 * This method is called when symbolic reduction ends
		 * up in a infinite loop and has been terminated.  This
		 * is just to alert you to the fact.
		 */
		void infiniteSymbolicReduction()
		{
			cout << "[Infinite Symbolic reduction detected]" << endl;
		}
		
		/**
		 * Sends you a message about a XMLParseError. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseError(const char * const message) 
		{ 
			cout << message << endl;
		} 

		/**
		 * Sends you a message about a XMLParseWarning. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseWarning(const char * const message)
		{ 
			cout << message << endl;
		} 

		/**
		 * Sends you a message about a XMLParseFatalError. 
		 *
		 * Either with AIML files or RebeccaAIML configuration
		 * files.
		 *
		 * \param message The human readable message.
		 */ 
		virtual void XMLParseFatalError(const char * const message) 
		{ 
			cout << message << endl;
		} 
		
		/**
		 * During runtime, the "thatStar" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void thatStarTagSizeExceeded() 
		{ 
			cout << "[Warning thatStar Tag Size Exceeded]" << endl;
		}
		
		/**
		 * During runtime, the "topicStar" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void topicStarTagSizeExceeded() 
		{ 
			cout << "[Warning topicStar Tag Size Exceeded]" << endl;		
		}

		/**
		 * During runtime, the "star" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void starTagSizeExceeded() 
		{ 
			cout << "[Warning star Tag Size Exceeded]" << endl;
		}

		/**
		 * A AIML "Input" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void inputTagNumericConversionError(const char * const message) 
		{ 
			cout << "inputTagNuermicConversionError:" << message << endl;		
		}

		/**
		 * During runtime, the "input" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void inputTagSizeExceeded() 
		{ 
			cout << "[Warning input Tag Size Exceeded]" << endl;
		} 

		/**
		 * A AIML "Star" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void starTagNumericConversionError(const char * const message) 
		{ 
			cout << "starTagNuermicConversionError:" << message << endl;				
		} 

		/**
		 * During runtime, the "that" AIML tag's size is 
		 * exceeded.
		 *
		 * Runtime is during a call to GraphBuilder::getResponse()
		 */
		virtual void thatTagSizeExceeded() 
		{ 
		
		}

		/**
		 * A AIML "That" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void thatTagNumericConversionError(const char * const message) 
		{ 
			cout << "thatTagNumericConversionError:" << message << endl;
		} 

		/**
		 * A AIML "TopicStar" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void topicStarTagNumericConversionError(const char * const message) 
		{ 
			cout << "topicStarTagNumericConversionError:" << message << endl;
		} 
		
		/**
		 * A AIML "thatStar" tag has a non number in its index attribute.
		 *
		 * This method will only be called during loadtime, GraphBuilder::createGraph().
		 *
		 * \param message The human readable message.
		 */
		virtual void thatStarTagNumericConversionError(const char * const message) 
		{ 
			cout << "thatStarTagNumericConversionError" << message << endl;
		}

};

/**
 * Parses and sets the 
 * arguments for main().
 */
class Arguments
{
	public:
		
		/**
		 * Constructor that
		 * sets the arguments up
		 * from main() as well
		 * as the program name its
		 * self.
		 *
		 * \param argc The number of arguments
		 * sent in.
		 *
		 * \param args The array of arguments 
		 */
		 Arguments(int argc, char* args[])
			: m_aimlSchemaPath("../../resources/schema/AIML.xsd"),
			  m_commonTypesSchemaPath("../resources/schema/common-types.xsd"),
			  m_botConfigurationSchemaPath("../resources/schema/bot-configuration.xsd"),
			  m_configurationDirectory("C:/Projects Base/Unification/Build/conf"),
			  m_aimlDirectory("C:/Projects Base/Unification/Build/aiml/annotated_alice"),
			  m_currentArgument(NO_ARG)
		{
			/*
			 * Iterate over the arguments
			 * and set them 
			 */
			for(int i = 1; i < argc; ++i)
			{
				//get string of the argument
				string argument(args[i]);
				
				if(m_currentArgument == NO_ARG)
				{
					if(argument == "-aimlSchema" || 
					   argument == "-as")
					{
						m_currentArgument = AIML_SCHEMA;					
					} 
					else if(argument == "-botSchema" ||
				            argument == "-bs")
					{
						m_currentArgument = BOT_SCHEMA;	
					}
					else if(argument == "-commonSchema" || 
						    argument == "-cs")
					{
						m_currentArgument = COMMON_SCHEMA;
					}
					else if(argument == "-configurationDirectory" || 
							argument == "-cd")
					{
						m_currentArgument = CONFIGURATION;
					}
					else if(argument == "-aimlDirectory" || 
						    argument == "-ad")
					{
						m_currentArgument = AIML;	
					}
					else if(argument == "-help" || 
						    argument == "-h" || 
							argument == "/?" ||
							argument == "--help")
					{
						/*
						 * Display help and exit
						 */
						cout << endl << endl
							 << "[console.exe help]" << endl
							 << "------------------" << endl << endl
							 << "Available switches:" << endl << endl
							 << "[-aimlSchema or -as]" << endl 
							 << "    AIML Schema Path (default is ../../resources/schema/AIML.xsd)" << endl << endl
							 << "[-botSchema or -bs] " << endl 
							 << "    Bot Schema Path (default is ../resources/schema/bot-configuration.xsd)" << endl << endl
							 << "[-commonSchema or -cs] " << endl
							 << "    Common Schema Path (default is ../resources/schema/common-types.xsd)" << endl << endl
							 << "[-configurationDirectory or -cd] " << endl
							 << "    Configuration directory (default is ../../conf)" << endl << endl
							 << "[-aimlDirectory or -ad] " << endl
							 << "    AIML directory with *.aiml files (default is ../../aiml/annotated_alice)" << endl << endl
							 << endl;
						exit(0);
					}
					else
					{
						cout << 
							"[Illegal argument of " +
							string(args[i]) +
							" found]" 
							<< endl;
					}
				}
				else
				{
					/*
					 * We already encountered the switch, 
					 * now we just need to set the argument
					 */
					if(m_currentArgument == AIML)
					{
						m_aimlDirectory = argument;
					}
					else if(m_currentArgument == AIML_SCHEMA)
					{
						m_aimlSchemaPath = argument;
					}
					else if(m_currentArgument == BOT_SCHEMA)
					{
						m_botConfigurationSchemaPath = argument;
					}
					else if(m_currentArgument == COMMON_SCHEMA)
					{
						m_commonTypesSchemaPath = argument;
					}
					else if(m_currentArgument == CONFIGURATION)
					{
						m_configurationDirectory = argument;
					}
					else
					{
						cout << "Programmer error "
							    "this should not be reached"
							 << endl;
					}

					m_currentArgument = NO_ARG;
				}
			}
		}
		
		/**
		 * Returns the configuration
		 * directory that has been set.
		 *
		 * \return The configuration directory
		 * where needed configuration files 
		 * are stored.
		 */
		string getConfigurationDirectory() const
		{
			return m_configurationDirectory;
		}
		
		/**
		 * Returns the AIML
		 * directory that has been set.
		 *
		 * \return The AIML directory
		 * where aiml files are stored.
		 */
		string getAimlDirectory() const
		{
			return m_aimlDirectory;
		}

		/**
		 * Returns the AIML schema
		 * path that has been set.
		 *
		 * \return The AIML schema 
		 * path that has been set.
		 */
		string getAimlSchemaPath() const
		{
			return m_aimlSchemaPath;
		}

		/**
		 * Returns the common types 
		 * schema path that has been set.
		 *
		 * \return The common types 
		 * schema path that has been set.
		 */
		string getCommonTypesSchemaPath() const
		{
			return m_commonTypesSchemaPath;
		}

		/**
		 * Returns the bot configuration
		 * schema path that has been set.
		 *
		 * \return the bot configuration
		 * schema path that has been set.
		 */
		string getBotConfigurationSchemaPath() const
		{
			return m_botConfigurationSchemaPath;
		}
		
		/** 
		 * Enumeration of possible switches you
		 * can give rebecca
		 */
		enum arguments{ NO_ARG, AIML, AIML_SCHEMA, 
			            COMMON_SCHEMA, BOT_SCHEMA, 
						CONFIGURATION};
		/**
		 * The current argument state.
		 */
		arguments m_currentArgument;

		/**
		 * The location of RebeccaAIML's
		 * configuration directory.  
		 *
		 * If this is not set, it will default 
		 * to the current working directory
		 * + "../../conf".  This is where
		 * needed configuration files are
		 * stored.
		 */
		string m_configurationDirectory;

		/**
		 * The location of a AIML directory.
		 *
		 * If this is not set, it will default
		 * to the current working directory 
		 * + "../../aiml/annotated_alice".
		 */
		string m_aimlDirectory;
		
		/**
		 * The path to the aiml xsd file.
		 * 
		 * If this is not set, it will default
         * to the current working directory + 
		 * "../../resources/schema/AIML.xsd"
		 */
		string m_aimlSchemaPath;

		/**
		 * The path to the the common types
		 * schema file.
		 * 
		 * If this is not set, it will default
         * to the current working directory + 
		 * "../resources/schema/common-types.xsd"
		 */
		string m_commonTypesSchemaPath;
		
		/**
		 * The path to the bot configuration
		 * schema file.
		 * 
		 * If this is not set, it will default
         * to the current working directory + 
		 * "../resources/schema/bot-configuration.xsd"
		 */
		string m_botConfigurationSchemaPath;
};