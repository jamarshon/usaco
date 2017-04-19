import math
def answer(area):
    # your code here
    retArr = []
    while area != 0:
    	closest_square = int(math.sqrt(area))
    	closest_square_area = closest_square*closest_square
    	area -= closest_square_area
        retArr.append(closest_square_area)

    return retArr

print answer(12)
