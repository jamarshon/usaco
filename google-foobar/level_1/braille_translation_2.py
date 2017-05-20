braille_map = {
    'a': '1',
    'b': '12',
    'c': '14',
    'd': '145',
    'e': '15',
    'f': '124',
    'g': '1245',
    'h': '125',
    'i': '24',
    'j': '245',
    'k': '13',
    'l': '123',
    'm': '134',
    'n': '1345',
    'o': '135',
    'p': '1234',
    'q': '12345',
    'r': '1235',
    's': '234',
    't': '2345',
    'u': '136',
    'v': '1236',
    'w': '2456',
    'x': '1346',
    'y': '13456',
    'z': '1356',
    ' ': '',
    'capital': '6'
}
 
values = ['1', '2', '3', '4', '5', '6']
for k, v in braille_map.iteritems():
    j = 0
    res = ''
    for i in range(len(values)):
        if j < len(v) and v[j] == values[i]:
            res += '1'
            j += 1
        else:
            res += '0'
    braille_map[k] = res
 
def answer(plaintext):
    res = ''
    for c in plaintext:
        if c in braille_map:
            res += braille_map[c]
        else:
            res += braille_map['capital'] + braille_map[c.lower()]
 
    return res
 
# Inputs:
plaintext = "code"
print answer(plaintext) == "100100101010100110100010"
 
# Inputs:
plaintext = "Braille"
print answer(plaintext) == "000001110000111010100000010100111000111000100010"
 
# Inputs:
plaintext = "The quick brown fox jumped over the lazy dog"
print answer(plaintext) == "000001011110110010100010000000111110101001010100100100101000000000110000111010101010010111101110000000110100101010101101000000010110101001101100111100100010100110000000101010111001100010111010000000011110110010100010000000111000100000101011101111000000100110101010110110"