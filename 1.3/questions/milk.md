The Merry Milk Makers company buys milk from farmers, packages it into attractive 1- and 2-Unit bottles, 
and then sells that milk to grocery stores so we can each start our day with delicious cereal and milk.

Since milk packaging is such a difficult business in which to make money, it is important to keep the 
costs as low as possible. Help Merry Milk Makers purchase the farmers' milk in the cheapest possible 
manner. The MMM company has an extraordinarily talented marketing department and knows precisely how 
much milk they need each day to package for their customers.

The company has contracts with several farmers from whom they may purchase milk, and each farmer 
has a (potentially) different price at which they sell milk to the packing plant. Of course, a 
herd of cows can only produce so much milk each day, so the farmers already know how much milk 
they will have available.

Each day, Merry Milk Makers can purchase an integer number of units of milk from each farmer, a 
number that is always less than or equal to the farmer's limit (and might be the entire production 
from that farmer, none of the production, or any integer in between).

Given:

The Merry Milk Makers' daily requirement of milk
The cost per unit for milk from each farmer
The amount of milk available from each farmer
calculate the minimum amount of money that Merry Milk Makers must spend to meet their daily need for milk.
Note: The total milk produced per day by the farmers will always be sufficient to meet the demands of 
the Merry Milk Makers even if the prices are high.

Here's how the MMM company spent only 630 cents to purchase 100 units of milk:
Price
per unit	Units
available	Units
bought	Price *
# units	Total cost	Notes
5	20	20	5*20	100
9	40	0			Bought no milk from farmer 2
3	10	10	3*10	30
8	80	40	8*40	320	Did not buy all 80 units!
6	30	30	6*30	180
Total	180	100		630	Cheapest total cost
