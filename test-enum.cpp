#include <iostream>
#include <string>

// compile: g++ test-enum.cpp

// // enum Color
// {
//	red = 0,
//	blue,

//	Count
// }; // compact representation

// enum SupportDeskTypes
// {
// 	eInvalid = -1,
// 	ePreWaitQueue = 0,	// support_desk:sdcust_prewait
// 	eSdcustQueue,		// support_desk:sdcust
// 	eGeneralQueue,		// support_desk:all_reps
// 	eRepPersonalQueue,	// support_desk:private:<#>
// 	eTeamQueue,		// support_desk:team:<#>
// 	eEmbassyTeamQueue,	// support_desk:embassy_team:<#>

// 	// others as grep-ed in trymax ...
// 	// they will be dealt with as more information is known about them
// 	//
// 	// support_desk:extended_contact_invitations
// 	// support_desk:invitation
// 	// support_desk:rep
// };

// SupportDeskTypes supportDeskType(const std::string& supportDesk) const
// {
// 	if (supportDesk.compare(0, 27, "support_desk:sdcust_prewait") == 0) {
// 		return SupportDeskTypes::ePreWaitQueue;
// 	} else if (supportDesk.compare(0, 20, "support_desk:sdcust") == 0) {
// 		return SupportDeskTypes::eSdcustQueue;
// 	} else if (supportDesk.compare(0, 22, "support_desk:all_reps") == 0) {
// 		return SupportDeskTypes::eGeneralQueue;
// 	} else if (supportDesk.compare(0, 20, "support_desk:private") == 0) {
// 		return SupportDeskTypes::eRepPersonalQueue;
// 	} else if (supportDesk.compare(0, 17, "support_desk:team") == 0) {
// 		return SupportDeskTypes::eTeamQueue;
// 	} else if (supportDesk.compare(0, 25, "support_desk:embassy_team") == 0) {
// 		return SupportDeskTypes::eEmbassyTeamQueue;
// 	} else {
// 		return SupportDeskTypes::eInvalid;
// 	}
// }

// int main()
// {
//	std::cout << supportDeskType("support_desk:sdcust_prewait") << std::endl;
//	std::cout << supportDeskType("support_desk:sdcust") << std::endl;
//	std::cout << supportDeskType("support_desk:all_reps") << std::endl;
//	std::cout << supportDeskType("support_desk:private:23") << std::endl;
//	std::cout << supportDeskType("support_desk:team:34") << std::endl;
//	std::cout << supportDeskType("support_desk:embassy_team:34") << std::endl;
//	std::cout << supportDeskType("") << std::endl;

//	// std::cout << ((Color::red < 9)?"yes":"no") << std::endl;
//	return 0;
// }

// #include <boost/asio.hpp>
// #include <boost/thread.hpp>
// #include <boost/bind.hpp>
#include <boost/preprocessor/enum.hpp>


// compile with: g++ -std=c++11 test-enum.cpp -lboost_system


BOOST_ENUM_VALUES(Level, const char*,
    (Abort)("unrecoverable problem")
    (Error)("recoverable problem")
    (Alert)("unexpected behavior")
    (Info) ("expected behavior")
    (Trace)("normal flow of execution")
    (Debug)("detailed object state listings")
)

int main()
{
	return 0;
}
