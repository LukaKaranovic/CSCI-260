/**
 * @file job.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 * Implements a job class defined in the 'job.h' header file.
 */

#include "job.h"
#include "dynamicarray.h"
#include <string>
#include <iostream>

using namespace std;


/** @brief Default Constructor
 *
*/

Job::Job(): _type("USER"), _exeTime(0), _userID("root"), _commandName("tempCommandName"), _resources("N/A") {}

/** @brief Regular Constructor
 *
*/

Job::Job(string& type, double time, string& userID, string& commandName, string& resources) {
    _type = type;
    _exeTime = time;
    _userID = userID;
    _commandName = commandName;
    _resources = resources;
}

/** @brief Destructor
 * 
*/

Job::~Job() {}

/** @brief Returns the job's type.
 *
 *  @return The type of job the job is. 
*/

string Job::getType() {
    return this->_type;
}

/** @brief Returns the job's estimated execution tie.
 *
 *  @return The estimated execution time of the job (ms).
*/

double Job::getTime() {
    return this->_exeTime;
}

/** @brief Returns the job's owner.
 *
 *  @return The Linux username of whoever requested the job. 
*/

string Job::getUser() {
    return this->_userID;
}

/** @brief Returns the job's command name.
 *
 *  @return The name of the command of the job.
*/

string Job::getCommand() {
    return this->_commandName;
}

/** @brief Returns the job's required resources.
 *
 *  @return The resources of the job.
*/

string Job::getResources() {
    return this->_resources;
}


/** @brief Prints all information of the job.
 *
 *  Job information includes job type, estimated execution time, owner of the job, 
 *  command name of the job, and the resources required for the job.
 *
 *  @return Void.
*/

void Job::displayInfo() {
    cout << "Job type: " << getType() << "\t Estimated execution time: " << getTime() << "\t User: " << getUser() << endl;
    cout << "Command name: " << getCommand() << "\t Resources: " << getResources() << endl;
    cout << endl;
}

/** @brief Converts the job's type into a numerical value.
 *
 *  If the job type is "SYSTEM" then it will return 0.
 *  If the job type is "USER" then it will return 1.
 *  The goal of this function is to help compare the priorities of jobs to ensure
 *  the job queue works properly.
 *
 *  @return 0 if type is "SYSTEM" and 1 if type is "USER".
*/

int Job::typePriority() {
    if (this->getType() == "SYSTEM") {
        return 0;
    }
    return 1;
}

/** @brief Checks if one job has a higher priority than another.
 *
 * Comparison operator (>) overload to see if one job is a higher priority in the queue than another.
 * If both jobs have the same type, the faster job has priority, otherwise system jobs have
 * priority over user jobs.
 *
 * @param job1 A job data type with a type and execution time.
 * @param job2 A job data type with a type and execution time.
 * @return True if job1 is a higher priority than job2. False if job1 isn't a higher priority than job2.
 */

bool operator > (Job& job1, Job& job2) {
    if (job1.typePriority() < job2.typePriority()) {
        return true;
    } else if (job1.getTime() < job2.getTime() && job1.typePriority() == job2.typePriority()) {
        return true;
    }
    return false;
}

/** @brief Checks if one job has a lower priority than another.
 *
 * Comparison operator (<) overload to see if one job is a lower priority in the queue than another.
 * If both jobs have the same type, the faster job has priority, otherwise system jobs have
 * priority over user jobs.
 *
 * @param job1 A job data type with a type and execution time.
 * @param job2 A job data type with a type and execution time.
 * @return True if job1 is a lower priority than job2. False if job1 isn't a lower priority than job2.
 */

bool operator < (Job& job1, Job& job2) {
    if (job1.typePriority() > job2.typePriority()) {
        return true;
    } else if (job1.getTime() > job2.getTime() && job1.typePriority() == job2.typePriority()) {
        return true;
    }
    return false;
}

/** @brief Checks if one job has the same priority as another job.
 *
 * Comparison operator (==) overload to see if one job has the same priority in the queue with another.
 * If both jobs have the same priority level, they have the same type and same execution time.
 *
 * @param job1 A job data type with a type and execution time.
 * @param job2 A job data type with a type and execution time.
 * @return True if job1 has the same priority as job2. False if job1 does not have the same priority as job2.
 */

bool operator == (Job& job1, Job& job2) {
    return (job1.typePriority() == job2.typePriority() && job1.getTime() == job2.getTime());
}

/** @brief Checks if one job does not have the same priority as another job.
 *
 * Comparison operator (!=) overload to see if one job does not have the same priority in the queue with another.
 * If both jobs don't have the same priority level, they have a different type and/or execution time.
 *
 * @param job1 A job data type with a type and execution time.
 * @param job2 A job data type with a type and execution time.
 * @return True if job1 does not have the same priority as job2. False if job1 has the same priority as job2.
 */

bool operator != (Job& job1, Job& job2) {
    return !(job1 == job2);
}

// Helper functions to convert a string to uppercase or lowercase (for user input friendliness).

/** @brief Converts the string to uppercase.
 *
 *  Changes the input string to make all of its characters uppercase.
 *
 *  @param input The input string.
 *  @return The input string in uppercase.
 */

string& stringToUpper(string& input) {
    int length = input.length();
    for (int i = 0; i < length; i++) {
        input[i] = toupper(input[i]);
    }
    return input;
}

/** @brief Converts the string to lowercase.
 *
 *  Changes the input string to make all of its characters lowercase.
 *
 *  @param input The input string.
 *  @return The input string in lowercase.
 */

string& stringToLower(string& input) {
    int length = input.length();
    for (int i = 0; i < length; i++) {
        input[i] = tolower(input[i]);
    }
    return input;
}