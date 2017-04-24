import math
import fractions

def is_equal(d1, d2):
    return abs(d1 - d2) <= 0.00000001

def is_same_pt(p1, p2):
    return is_equal(p1[0], p2[0]) and is_equal(p1[1], p2[1])

def get_dist(p1, p2):
    dx = p1[0]-p2[0]
    dy = p1[1]-p2[1]
    return math.sqrt(dx*dx + dy*dy)

def get_slope(p1, p2):
    dx = p1[0]-p2[0]
    dy = p1[1]-p2[1]
    if is_equal(abs(dx), 0):
        prefix = 'up-' if dy > 0 else 'down-'
        return prefix + 'x=' + str(p1[0])
    elif is_equal(abs(dy), 0):
        prefix = 'right-' if dx > 0 else 'left-'
        return prefix + 'y=' + str(p1[1])
    else:
        prefix = 'right-' if dx > 0 else 'left-'
        dgcd = fractions.gcd(dy, dx)
        a = dy/dgcd
        b = dx/dgcd
        return prefix + str(a) + '/' + str(b)

def get_range(dimensions, pt, captain_position, distance, i):
    intial_val = pt[i]
    low_val = captain_position[i] - distance
    high_val = captain_position[i] + distance

    offset_val = [2*dimensions[i] - 2*pt[i], 2*pt[i]]
    offset_val_ind = 0
    range_val = []

    temp = intial_val
    while temp <= high_val:
        range_val.append(temp)
        temp += offset_val[offset_val_ind]
        offset_val_ind ^= 1

    temp = range_val.pop(0)
    offset_val_ind = 1
    while temp >= low_val:
        range_val.insert(0, temp)
        temp -= offset_val[offset_val_ind]
        offset_val_ind ^= 1

    return range_val

def get_slope_min_dist_map(dimensions, pt, captain_position, distance):
    range_x = get_range(dimensions, pt, captain_position, distance, 0)
    range_y = get_range(dimensions, pt, captain_position, distance, 1)
    slope_min_dist_map = {}
    for i in range_x:
        for j in range_y:
            potential_pt = [i, j]
            if not is_same_pt(potential_pt, captain_position):
                dist = get_dist(potential_pt, captain_position)
                if dist <= distance:
                    slope = get_slope(potential_pt, captain_position)
                    if slope in slope_min_dist_map:
                        if slope_min_dist_map[slope][0] > dist:
                            slope_min_dist_map[slope] = [dist, potential_pt]
                    else:
                        slope_min_dist_map[slope] = [dist, potential_pt]
    return slope_min_dist_map

def answer(dimensions, captain_position, badguy_position, distance):
    captain_map = get_slope_min_dist_map(dimensions, captain_position, captain_position, distance)
    badguy_map = get_slope_min_dist_map(dimensions, badguy_position, captain_position, distance)
    count = 0
    for slope in badguy_map:
        if slope in captain_map:
            if badguy_map[slope] < captain_map[slope]:
                count += 1
        else:
            count += 1
    return count

print answer([3, 2], [1, 1], [2, 1], 4) 
print answer([300, 275], [150, 150], [185, 100], 500)
print answer([42, 59], [34, 44], [6, 34], 5000)