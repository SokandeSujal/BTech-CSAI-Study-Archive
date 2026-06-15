% Medical Diagnosis Expert System
% Facts - Symptoms
symptom(fever).
symptom(cough).
symptom(headache).
symptom(sore_throat).
symptom(body_ache).
symptom(runny_nose).
symptom(fatigue).
symptom(nausea).

% Rules - Diseases based on symptoms
disease(flu) :-
    has_symptom(fever),
    has_symptom(cough),
    has_symptom(body_ache),
    has_symptom(fatigue).

disease(cold) :-
    has_symptom(runny_nose),
    has_symptom(sore_throat),
    has_symptom(cough).

disease(covid) :-
    has_symptom(fever),
    has_symptom(cough),
    has_symptom(fatigue),
    has_symptom(body_ache).

disease(migraine) :-
    has_symptom(headache),
    has_symptom(nausea).

disease(throat_infection) :-
    has_symptom(sore_throat),
    has_symptom(fever).

% Treatment recommendations
treatment(flu, 'Rest, drink fluids, take antipyretics').
treatment(cold, 'Rest, warm liquids, steam inhalation').
treatment(covid, 'Isolate, consult doctor, monitor oxygen levels').
treatment(migraine, 'Rest in dark room, take painkillers').
treatment(throat_infection, 'Gargle with salt water, antibiotics if bacterial').

% Diagnosis procedure
diagnose :-
    write('Medical Diagnosis Expert System'), nl,
    write('Answer yes/no to the following questions:'), nl, nl,
    check_symptoms,
    find_disease.

% Check symptoms
check_symptoms :-
    retractall(has_symptom(_)),
    ask_symptom(fever),
    ask_symptom(cough),
    ask_symptom(headache),
    ask_symptom(sore_throat),
    ask_symptom(body_ache),
    ask_symptom(runny_nose),
    ask_symptom(fatigue),
    ask_symptom(nausea).

% Ask about a symptom
ask_symptom(S) :-
    write('Do you have '), write(S), write('? (yes/no): '),
    read(Answer),
    (Answer = yes -> assert(has_symptom(S)) ; true).

% Find and suggest disease
find_disease :-
    disease(D),
    !,
    write('Possible diagnosis: '), write(D), nl,
    treatment(D, T),
    write('Recommended treatment: '), write(T), nl.

find_disease :-
    write('No specific diagnosis found. Consult a doctor.'), nl.

% Start diagnosis
:- initialization(diagnose, main).
