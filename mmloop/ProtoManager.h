#pragma once
#ifndef _PROTO_MANAGER_H_
#define _PROTO_MANAGER_H_
#include <map>

namespace mm {
	namespace Proto {

		// protocol Family

		class protoFamily
		{
		public:
			protoFamily(const char* type);
			~protoFamily();
			inline char* protocol() { return (char*)prototype; }
			virtual void parse() = 0;
		protected:
			static const char*  prototype;
			void* data;
		};

		// protocol Test

		class protoTest : public protoFamily
		{
		public:
			protoTest(const char* type);
			~protoTest();
			virtual void parse();
		private:

		};

		
		// protocol Manager

		class protoManager
		{
		public:
			enum PF
			{
				INVALID = -1,
				MQTT = 0,
				HTTP,
				FTP,
				TEST
			};
		public:
			protoManager(const protoFamily& pf);
			~protoManager();
			bool Register();
			bool Deregister();
		private:
			std::map<std::string, protoFamily&> prototable;
		};

		
	}
}//namespace mm::Proto
#endif // !_PROTO_MANAGER_H_
