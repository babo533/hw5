#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillSchedule(const AvailabilityMatrix& avail,
                  const size_t dailyNeed,
                  const size_t maxShifts,
                  DailySchedule& sched,
                  vector<size_t>& shiftNum,
                  size_t curDay,
                  size_t num);


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
  if(avail.size() == 0U){
      return false;
  }
  sched.clear();
  // Add your code below

  if (avail.size() > 0) {
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID)); // need to resize or seg fault
  } 
  else {
    sched.resize(0);
  }

  vector<size_t> numShifts;
  
  if (!avail.empty()) {
    numShifts.resize(avail[0].size(), 0);
  } 
  else {
    numShifts.resize(0);
  }

  return fillSchedule(avail, dailyNeed, maxShifts, sched, numShifts, 0, 0);
}

bool fillSchedule(const AvailabilityMatrix& avail,
                  const size_t dailyNeed,
                  const size_t maxShifts,
                  DailySchedule& sched,
                  vector<size_t>& shiftNum,
                  size_t curDay,
                  size_t num)
{
  if (curDay >= avail.size()) {
    return 1; //all days are filled
  }

  if (num >= dailyNeed) {
    // proceed to next day if met
    return fillSchedule(avail, dailyNeed, maxShifts, sched, shiftNum, curDay + 1, 0);
  }

  for (size_t i = 0; i < avail[curDay].size(); ++i) {
    if (avail[curDay][i] && shiftNum[i] < maxShifts) {
      shiftNum[i]++; //change worker shifts by 1
      sched[curDay][num] = i; // assign worker i to this shift
      bool result = fillSchedule(avail, dailyNeed, maxShifts, sched, shiftNum, curDay, num + 1);
      if (result) {
        return 1; //if schedule works out return true
      }

      // backtrack if not and keep going and decrement the shift
      shiftNum[i]--;
      sched[curDay][num] = INVALID_ID;
    }
  }

  return 0; // if no combinations return false
}