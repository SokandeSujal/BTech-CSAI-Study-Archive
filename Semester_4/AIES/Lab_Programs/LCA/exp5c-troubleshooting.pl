% Computer Troubleshooting

start :-
    write('Is computer not turning on? (yes/no): '), read(Power),
    write('Is screen blank? (yes/no): '), read(Screen),
    write('Is system slow? (yes/no): '), read(Slow),

    solution(Power, Screen, Slow).

solution(yes, _, _) :-
    write('Check power cable or battery').

solution(no, yes, _) :-
    write('Check display or monitor connection').

solution(no, no, yes) :-
    write('Close background apps or restart system').

solution(_, _, _) :-
    write('Contact technician').