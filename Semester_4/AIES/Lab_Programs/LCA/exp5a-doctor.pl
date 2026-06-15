% Disease Diagnosis

start :-
    write('Do you have fever? (yes/no): '), read(Fever),
    write('Do you have cough? (yes/no): '), read(Cough),
    write('Do you have headache? (yes/no): '), read(Head),

    diagnose(Fever, Cough, Head).

diagnose(yes, yes, yes) :-
    write('You may have Flu').

diagnose(yes, no, yes) :-
    write('You may have Viral Fever').

diagnose(no, yes, no) :-
    write('You may have Cold').

diagnose(_, _, _) :-
    write('Consult a doctor').