#include "ProtoManager.h"

namespace mm {
	namespace Proto {
	
		const char* protoFamily::prototype = NULL;

		protoFamily::protoFamily(const char* type)
		{
			prototype = type;
		}

		protoFamily::~protoFamily()
		{
		}


		protoTest::protoTest(const char* type) :protoFamily(type)
		{
		}

		protoTest::~protoTest()
		{
		}

		void protoTest::parse()
		{
		}



		protoManager::protoManager(const protoFamily& pf)
		{
		}

		protoManager::~protoManager()
		{
		}

		bool protoManager::Register()
		{
			return true;
		}

		bool protoManager::Deregister()
		{
			return true;
		}
	
	}

}//namespace mm::Proto