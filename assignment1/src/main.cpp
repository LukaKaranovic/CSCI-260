/**
 * @file main.cpp
 * @author Luka Karanovic, 665778833, F24N03, CSCI 260, VIU
 * @version 1.0.4
 * @date September 24, 2024
 *
 */

#include <iostream>
#include <algorithm>
#include <string>
#include "../include/job.h"
#include "../include/jobqueue.h"

using namespace std;

/** @brief Prompts the user for a command returns it.
 *
 *  Converts the command input to lowercase so it works for the conditional statements in main. This adds user input friendliness.
 *
 *  @param userCommand The string used to store the user's command.
 *  @return The inputted user command in lowercase.
 */

string& getCommand(string& userCommand) {
    cout << "Enter a command: ";
    getline(cin, userCommand);
    return stringToLower(userCommand);
}

/** @brief Prompts the user to enter information for a job to add to the job queue.
 *
 *  If an invalid argument is entered, the program will throw an exception and prompt the user for a new command input.
 *
 *  @return The job created from the user's inputted information.
 */

Job submit() {
    string type;
    double time;
    string user;
    string command;
    string resources;

    cout << "Enter the type of job (SYSTEM or USER): ";
    getline(cin, type);
    if (stringToUpper(type) == "SYSTEM") {
        type = "SYSTEM";
    } else if (stringToUpper(type) == "USER") {
        type = "USER";
    } else {
        throw invalid_argument("Job type must be either \"SYSTEM\" or \"USER\".");
    }

    cout << "What is the estimated execution time for your job (ms)?: ";
    cin >> time;
    cin.ignore(1000, '\n');
    if (time < 0) {
        throw invalid_argument("Job time cannot be negative.");
    }

    cout << "Enter the command for the job: ";
    getline(cin, command);

    cout << "Who started this job?: ";
    getline(cin, user);

    cout << "Enter the resources for the job: ";
    getline(cin, resources);

    Job job(type, time, user, command, resources);
    return job;
}

/** @brief Executes the job that's first in the priority queue. Displays its information and removes it from the job queue.
 *
 *  @return Void.
 */

void execute(JobQueue& jobs) {
    if (jobs.isEmpty()) {
        cout << "No jobs available to execute." << endl;
        return;
    }
    cout << "Executing job..." << endl;
    jobs.removeMin().displayInfo();
}

/** @brief Executes a random job in the job queue. Displays its information and removes it from the job queue.
 *
 *  @return Void.
 */

void lottery(JobQueue& jobs) {
    if (jobs.isEmpty()) {
        cout << "No jobs available to execute." << endl;
        return;
    }
    cout << "Executing random job..." << endl;
    int index = rand() % jobs.getSize();
    (jobs.removeAt(index)).displayInfo();
}

/** @brief Executes every job in the job queue in order of priority. Terminates the program afterwards.
 *
 *  @return Void.
 */

void quit(JobQueue& jobs) {
    cout << "Program is being terminated, deleting job queue." << endl;
    while (!jobs.isEmpty()) {
        jobs.removeMin().displayInfo();
    }
    cout << "All jobs are killed. Terminating the program." << endl;
    cout << "Thank you for using the program!" << endl;
}

int main() {
    JobQueue jobs;
    string userCommand;
    cout << "Command list: " << endl;
    cout << "submit: Submit a new job request." << endl;
    cout << "execute: Removes the job with the highest priority from the job queue." << endl;
    cout << "lottery: Randomly removes a lucky job from the job queue." << endl;
    cout << "quit: Terminates the program.." << endl;

    getCommand(userCommand);
    while (userCommand != "quit") {
        if (userCommand == "submit") {
            try {
                jobs.insert(submit());
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else if (userCommand == "execute") {
            try {
                execute(jobs);
            } catch (invalid_argument& error) {
                cout << error.what() << endl;
            }
        } else if (userCommand == "lottery") {
            lottery(jobs);
        } else if (userCommand == "queue") {
            jobs.displayQueue();
        } else {
            cout << "Not a valid command, try again." << endl;
        }
        getCommand(userCommand);
    }
    quit(jobs);
    return 0;
}