# Translator-Of-Polinomials
This is a help sheet!\
You can chose different data structures by using swtich and its full name \
or the short notation in the brackets (case sensitive):
1) SortedTable (st)
2) UnsortedTable (ut)
3) BRtree (br)
4) AVLtree (av)
5) ChainedHashTable (ht/h1)
6) ProbingHashTable (ho/h2)

You can insert polynoms by using this syntax:\
`<key>` = `<your_polynom>` (ex. a=16x^2yz)\
`<key>` = `<arithmetic expression with already existing polynoms>` (ex. a=b+c)

`run_test`  - will run gtests\
`switch` `<name>` - will switch data structure (`st, ut, av, br, ht, ho`)\
`status` - will print current data structure status\
`show`/`show <number>` - will print out all or the specified number of the stored polynoms along with their keys\
`del` `<key>` - will delete polynom with specified key