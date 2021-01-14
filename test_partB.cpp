#include "../part2/base_event.h"
#include "../part2/closed_event.h"
#include "../part2/custom_event.h"
#include "../part1/date_wrap.h"
#include "../part2/event_container.h"
#include "../part1/exceptions.h"
#include "../part2/festival.h"
#include "../part2/one_time_event.h"
#include "../part2/open_event.h"
#include "../part2/recurring_event.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;
typedef mtm::EventContainer::EventIterator Iter;


#define ASSERT_TEST(expr)                                                         \
     do {                                                                          \
         if (!(expr)) {                                                            \
             cout << "\nAssertion failed at"<< __FILE__<< __LINE__ << #expr << endl; \
             result = false;                                                       \
         }                                                                         \
     } while (0);

#define RUN_TEST(test, name)                  \
    do {                                 \
        cout << "+ Running" << name << "...";  \
        if (test()) {                    \
            cout << "[OK]\n" << endl;         \
        } else {                         \
            cout << "[Failed]\n\n <span>To see what the test does and why it failed, please check the link at the top of the page to the test file</span>" << endl;       \
        }                                \
    } while (0);


class FileFailed{
public:
    FileFailed() = default;
    ~FileFailed() = default;
};

class FileOutputWrong{
public:
    FileOutputWrong() = default;
    ~FileOutputWrong() = default;
};


bool matchFiles(const char* out,const char*  exp){
    ifstream output(out);
    if(!output){
        cout << "can't open file" << endl;
    }
    ifstream expOutput(exp);
    if(!expOutput){
        cout << "can't open file" << endl;
    }
    while(!output.eof()){
        char c;
        output >> c;
        char ex;
        expOutput >> ex;
        if(ex != c) {
            return false;
        }
    }
    return true;
}

void printEventsShort(mtm::EventContainer& events, ofstream& stream) {
    for (Iter iter = events.begin(); iter != events.end(); ++iter) {
        mtm::BaseEvent &event = *iter;
        event.printShort(stream);
    }
}





/**__________________________________________________________________________*/
/** HERE START THE TESTS*/
bool test1SegelProvided() {
    bool result = true;
    const char* fileName = "../../provided/testOutputs/your_outputs/test1SegelProvided.txt";
    std::ofstream out(fileName, std::ios_base::in);
    out.open(fileName);
    if(!out.is_open()){
        throw FileFailed();
    }
    mtm::Festival festival(mtm::DateWrap(21, 10, 2020));
    festival.add(mtm::OpenEvent(mtm::DateWrap(21, 10, 2020), "Performance 1"));
    mtm::ClosedEvent closed(mtm::DateWrap(21, 10, 2020), "Performance 2");
    closed.addInvitee(1);
    closed.addInvitee(500);
    festival.add(closed);
    printEventsShort(festival,out);

    mtm::RecurringEvent<mtm::OpenEvent> recurring(mtm::DateWrap(21, 10, 2020),
                                                  "Wednesday Noon", 13, 7);
    printEventsShort(recurring, out);

    mtm::OneTimeEvent<mtm::OpenEvent> one_time(mtm::DateWrap(2, 3, 80),
                                               "A long time ago");
    printEventsShort(one_time, out);
    out.close();
    ASSERT_TEST(matchFiles(fileName, "../../provided/testOutputs/expected/test1SegelProvided.txt"))
    return result;
}

void test2SegelProvided_aux(mtm::BaseEvent& event, ofstream& stream) {
    event.registerParticipant(1);
    event.registerParticipant(20000);
    event.unregisterParticipant(1);
    event.registerParticipant(3);
    mtm::BaseEvent *clone = event.clone();
    clone->printShort(stream);
    clone->printLong(stream);
    delete clone;
}

struct StudentFilter {
    bool operator()(int student) {
        return student == 1 || student == 3 || student == 20000;
    }
};

bool test2SegelProvided() {
    bool result = true;
    const char* fileName = "../../provided/testOutputs/your_outputs/test2SegelProvided.txt";
    std::ofstream out(fileName, std::ios_base::in);
    out.open(fileName);
    if(!out.is_open()){
        throw FileFailed();
    }
    mtm::OpenEvent open(mtm::DateWrap(21, 10, 2020), "An Open Event");
    test2SegelProvided_aux(open, out);

    mtm::ClosedEvent closed(mtm::DateWrap(21, 10, 2020), "A Closed Event");
    closed.addInvitee(1);
    closed.addInvitee(3);
    closed.addInvitee(20000);
    test2SegelProvided_aux(closed, out);
    mtm::CustomEvent<StudentFilter> custom(mtm::DateWrap(21, 10, 2020),
                                           "A Custom Event", StudentFilter());
    test2SegelProvided_aux(custom, out);
    out.close();
    ASSERT_TEST(matchFiles(fileName,"../../provided/testOutputs/expected/test2SegelProvided.txt" ))
    return result;
}

bool testConstructorOpenEvent
const int NUMBER_OF_TESTS = 2;

#define TEST_NAMES \
    X(test1SegelProvided) \
    X(test2SegelProvided)

const char *testNames[] = {
#define X(name) #name,
        TEST_NAMES
#undef X
};
bool (*tests[])(void) = {
#define X(test_name) test_name,
        TEST_NAMES
#undef X
};


int main(int argc, char* argv[]) {
    if (argc < 2) {
        for(int i = 0; i < NUMBER_OF_TESTS ; i++){
            RUN_TEST(tests[i], testNames[i])
        }
    } else if (argc > 2) {
        std::cout << "invalid arguments" << std::endl;
    } else {
        int i = std::atoi(argv[1]);
        tests[i - 1]();
    }
    return 0;
}
