% Career Guidance

start :-
    write('Do you like coding? (yes/no): '), read(Coding),
    write('Do you like maths? (yes/no): '), read(Maths),
    write('Do you like biology? (yes/no): '), read(Bio),

    suggest(Coding, Maths, Bio).

suggest(yes, yes, no) :-
    write('Career: Software Engineer').

suggest(no, yes, yes) :-
    write('Career: Doctor').

suggest(no, no, yes) :-
    write('Career: Biologist').

suggest(yes, no, no) :-
    write('Career: Web Developer').

suggest(_, _, _) :-
    write('Explore multiple fields').