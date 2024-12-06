/**
 * @file job.h
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 * Job encapsulates all of the data required for a job stated in the specifications section: type, time, userID, commandName, and resources.
 * Job has constructors, destructors, getter functions, a typePriority() method which returns an integer value for the job's type (used for comparison operators), a displayInfo() method which prints the object's information, and overloads comparison operators to help compare one job's priority with another.
 * At the moment, there isn't a way to modify a job's data once it is created.
 */


#ifndef ASSN1_JOB_H
#define ASSN1_JOB_H

#include <string>
#include <ostream>

using namespace std;

class Job {
protected:
    string _type;           // The type of the job
    double _exeTime;        // Estimated execution time of the job
    string _userID;         // User who requested the job
    string _commandName;    // Command name of the job
    string _resources;      // Resources required for the job

public:
    /**
	 * Default constructor
	 */
    Job();

    /**
	 * Regular constructor
	 */
    Job(string& type, double time, string& userID, string& commandName, string& resources);
    
    /**
	 * Destructor
	 */
    ~Job();

	/**
	 * Returns the type of the job.
	 */
    string getType();

	/**
	 * Returns the estimated execution time of the job.
	 */
    double getTime();

	/**
	 * Returns the userID of who requested the job.
	 */
    string getUser();

	/**
	 * Returns the command name of the job.
	 */
    string getCommand();

	/**
	 * Returns the resources this job requires.
	 */
    string getResources();

	/**
	 * Displays all information about the job at once.
	 */
    void displayInfo();

    /**
     * Returns the priority of a job based on type. System = 0, User = 1.
     */
    int typePriority();

    /**
	 * Comparison operator overload to see if one job is a higher priority in the queue than another.
     * If both jobs have the same type, the faster job has priority, otherwise system jobs have
     * priority over user jobs.
	 */
    friend bool operator > (Job& job1, Job& job2);

    /**
	 * Comparison operator overload to see if one job is a lower priority in the queue than another.
     * If both jobs have the same type, the faster job has priority, otherwise system jobs have
     * priority over user jobs.
	 */
    friend bool operator < (Job& job1, Job& job2);

    /**
	 * Comparison operator overload to see if one job has the same priority in the queue with another.
     * If both jobs have the same priority level, they have the same type and same execution time.
	 */
    friend bool operator == (Job& job1, Job& job2);

    /**
	 * Comparison operator overload to see if one job does not have the same priority in the queue with another.
     * If both jobs don't have the same priority level, they have a different type and/or execution time.
	 */
    friend bool operator != (Job& job1, Job& job2);

};


// Helper functions to convert a string to uppercase or lowercase (for user input friendliness).


/**
 * Converts the string to uppercase.
 */
string& stringToUpper(string& input);

/**
 * Converts the string to lowercase.
 */
string& stringToLower(string& input);

#endif