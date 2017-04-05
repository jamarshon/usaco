A group of NP (2 ≤ NP ≤ 10) uniquely named friends has decided to exchange gifts of 
money. Each of these friends might or might not give some money to any or all of the 
other friends. Likewise, each friend might or might not receive money from any or all 
of the other friends. Your goal in this problem is to deduce how much more money each 
person gives than they receive.

The rules for gift-giving are potentially different than you might expect. Each person 
sets aside a certain amount of money to give and divides this money evenly among all those 
to whom he or she is giving a gift. No fractional money is available, so dividing 3 among 
2 friends would be 1 each for the friends with 1 left over -- that 1 left over stays in 
the giver's "account".

In any group of friends, some people are more giving than others (or at least may have more 
acquaintances) and some people have more money than others.

Given a group of friends, no one of whom has a name longer than 14 characters, the money 
each person in the group spends on gifts, and a (sub)list of friends to whom each person 
gives gifts, determine how much more (or less) each person in the group gives than they receive.

Five names: dave, laura, owen, vick, amr Let's keep a table of the gives (money) each person 'has':
dave	laura	owen	vick	amr
0	0	0	0	0
First, 'dave' splits 200 among 'laura', 'owen', and 'vick'. That comes to 66 each, with 2 left over
-200+2	66	66	66	0
Second, 'owen' gives 500 to 'dave':
-198+500	66	66-500	66	0
Third, 'amr' splits 150 between 'vick' and 'owen':
302	66	-434+75	66+75	-150
Fourth, 'laura' splits 0 between 'amr' and 'vick'; no changes:
302	66	-359	141	-150
Finally, 'vick' gives 0 to no one:
dave	laura	owen	vick	amr
302	66	-359	141	-150