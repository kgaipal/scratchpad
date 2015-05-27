// Compilation instructions:
// g++ -std=gnu++11 -ljsoncpp test-json.cpp

#include <jsoncpp/json/json.h>

#include <iostream>
#include <string>
#include <sstream>

// const std::string config_doc =
// "{ \
//     \"encoding\" : \"UTF-8\", \
//  \
//     \"plug-ins\" : [ \
// 	\"python\", \
// 	\"c++\", \
// 	\"ruby\" \
// 	], \
//  \
//     \"indent\" : { \"length\" : 3, \"use_space\": true } \
// }";

const std::string credentials =
"{\
	\"type\": \"authenticate\",\
	\"credentials\":\
	{\
		\"username\": \"<username>\",\
		\"password\": \"<password>\"\
	}\
}";

const std::string subscribe =
"{\
  \"type\": \"subscribe\",\
  \"tables\": [\"support_session\"]\
}";

//  \"tabless\": \"all\"				\
//  \"tables\": [\"support_session\", \"rep_session\"]\

bool stringToJson(const std::string& src, Json::Value& root)
{
	Json::Reader reader;
	const bool success = reader.parse(src, root);

	if (!success) {

#ifdef _DEBUG
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n"
			   << reader.getFormatedErrorMessages();
#endif
		return false;
	}

	return true;
}

int main()
{
	Json::Value root;

// #ifdef _DEBUG
// 	std::cout << "--" << credentials << "--" ;
// #endif

	// if (stringToJson(credentials, root)) {
// 		std::cout << root["type"].asString() << std::endl;
// 		std::cout << root["credentialss"].get("username", "-").asString() << std::endl;
// 		std::cout << root["credentials"].get("password", "").asString() << std::endl;
	// }

	// if (stringToJson(subscribe, root)) {
	// 	const Json::Value tables = root["tables"];
	// 	std::cout << tables.size() << std::endl;

	// 	// might be a request for "all" tables
	// 	if (tables.size() == 0) {
	// 		std::cout << tables.asString() << std::endl;

	// 	} else {
	// 		for (int i = 0; i < tables.size(); i++) {
	// 			const std::string tableName = tables[i].asString();
	// 			std::cout << tableName << std::endl; 
	// 		}
	// 	}
	// }

	// root["type"] = "authenticate_response";
	// root["success"] = true;

	// root["type"] = "update_model";       
	// {
	// 	{
	// 		root["delete"]["0"].append(Json::Value(-1));
	// 		root["delete"]["0"].append(Json::Value(-2));
	// 		root["delete"]["0"].append(Json::Value(-3));
	// 	}
	// 	{
	// 		root["delete"]["0"].append(Json::Value(1));
	// 		root["delete"]["0"].append(Json::Value(2));
	// 		root["delete"]["0"].append(Json::Value(3));
	// 	}
	// 	// {
	// 	// 	Json::Value vec(Json::arrayValue);
	// 	// 	vec.append(Json::Value(1));
	// 	// 	vec.append(Json::Value(2));
	// 	// 	vec.append(Json::Value(3));
	// 	// 	root["delete"]["0"] = vec;
	// 	// }
	// }
	// root["delete"]["3"] = "";

	for (int i = 0; i < 3; i++) {
		Json::Value subtree;

		for (int j = 0; j < 2; j++) {
			std::string index, value;

			{
				std::stringstream ss;
				ss << "index_" << i<< "," << j;
				index = (ss.str());
			}

			{
				std::stringstream ss;
				ss << "value_" << i<< "," << j;
				value = ss.str();
			}
			subtree[index] = Json::Value(value);
		}

		root.append(subtree);
	}

	Json::FastWriter writer;
	std::cout << writer.write(root);

	return 0;
}
