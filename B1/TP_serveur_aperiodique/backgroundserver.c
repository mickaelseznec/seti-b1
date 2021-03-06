#include "events.h"
#include "periodictasks.h"
#include "tasks.h"

// Main procedure of background server

void *runBackgroundServer (void *t){
  TaskInfo           s;
  EventInfo          e;
  Time               d = 0;

  s = periodicTaskTable[*(int *)t];

  while (systemNotCompleted() && (0 <= lastEvent)) {
    e = getEvent(firstEvent);
    
    // Wait for event activation
    delayUntil(e.activation);

    putHeader(s.name);
    putString(s.name);
    putString("=+oo ");
    putString(e.name);
    putString("=");
    putTime  (e.computation);
    newLine();

    // Remove first event from event queue
    removeEvent(0);

    // Simulate the execution of this event using
    // computeDuringTimeSpan. Provide the name of the event, its worst
    // case execution time, and the period of the server. ATTENTION :
    // the period parameter in computeDuringTimeSPan is used to
    // compute the execution priority. See in tasks.h.
    computeDuringTimeSpan(s.name, e.computation, s.period);

    // Print event completion
    putHeader(s.name);
    putString("C=oo ");
    putString(e.name);
    putString(" completed");
    newLine();
  }

  return NULL;
}
