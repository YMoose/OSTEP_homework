#! /usr/bin/env python

import sys
from optparse import OptionParser
import random
import matplotlib.pyplot as plt

parser = OptionParser()
parser.add_option('-s', '--seed', default=0, help='the random seed',              action='store', type='int', dest='seed')
parser.add_option('-l', '--jlist', default='', help='instead of random jobs, provide a comma-separated list of run times and ticket values (e.g., 10:100,20:100 would have two jobs with run-times of 10 and 20, each with 100 tickets), have to be 2 jobs',  action='store', type='string', dest='jlist')
parser.add_option('-m', '--maxlen',  default=100,  help='max length of job',         action='store', type='int', dest='maxlen')
parser.add_option('-T', '--maxticket', default=100, help='maximum ticket value, if randomly assigned',          action='store', type='int', dest='maxticket')
parser.add_option('-q', '--quantum', default=1,   help='max length of time slice', action='store', type='int', dest='quantum')
parser.add_option('-c', '--compute', help='compute answers for me', action='store_true', default=True, dest='solve')
parser.add_option('-p', '--path', help='graph save path', action='store', type='string', default='./result.png', dest='path')


(options, args) = parser.parse_args()
options.jobs = 2

random.seed(options.seed)

print ('ARG jlist', options.jlist)
print ('ARG jobs', options.jobs)
print ('ARG maxlen', options.maxlen)
print ('ARG maxticket', options.maxticket)
print ('ARG quantum', options.quantum)
print ('ARG seed', options.seed)
print ('ARG path', options.path)
print ('')

import operator

plt.figure()
unfairness = []
repeat_index = []
for j in range(options.maxlen):
    if (j == 0):
        continue
    tickTotal = 0
    runTotal  = 0
    joblist = []
    if options.jlist == '':
            runtime = 0
            while runtime == 0:
                runtime = j
            tickets = 0
            while tickets == 0:
                tickets = int(options.maxticket * random.random())
            runTotal = runtime << 1
            tickTotal = tickets << 1
            joblist.append([0, runtime, tickets])
            joblist.append([1, runtime, tickets])
    else:
        jobnum = 0
        for entry in options.jlist.split(','):
            if (len(joblist) > 2):
                break
            (runtime, tickets) = entry.split(':')
            if (int(runtime) == 0):
                print ('Error: Job runtime cannot be 0')
                sys.exit(0)
            joblist.append([jobnum, int(runtime), int(tickets)])
            runTotal += int(runtime)
            tickTotal += int(tickets)
            jobnum += 1

    if (len(joblist) != 2):
        print ('Error: Jobs quantity, have to be 2')
        sys.exit(0)
    
    if options.solve == True:
        
        jobs  = len(joblist)
        clock = 0
        endtime = []
        for i in range(runTotal):
            r = int(random.random() * 1000001)
            winner = int(r % tickTotal)

            current = 0
            for (job, runtime, tickets) in joblist:
                current += tickets
                if current > winner:
                    (wjob, wrun, wtix) = (job, runtime, tickets)
                    break

            # now do the accounting
            if wrun >= options.quantum:
                wrun -= options.quantum
            else:
                wrun = 0

            clock += options.quantum

            # job completed!
            if wrun == 0:
                endtime.append(clock)
                tickTotal -= wtix
                wtix = 0
                jobs -= 1

            # update job list
            joblist[wjob] = (wjob, wrun, wtix)

            if jobs == 0:
                repeat_index.append(j)
                unfairness.append(endtime[0]/endtime[1])
                break
plt.plot(repeat_index, unfairness)
plt.legend()
plt.savefig(options.path)
    




