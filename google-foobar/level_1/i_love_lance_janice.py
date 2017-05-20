def answer(s):
    a = ord('a')
    z = ord('z')
    res = ''
    for c in s:
        ord_c = ord(c)
        if  a <= ord_c <= z:
            res += chr(z + a - ord_c)
        else:
            res += c
    return res

s = "wrw blf hvv ozhg mrtsg'h vkrhlwv?"
print answer(s), "did you see last night's episode?"

s = "Yvzs! I xzm'g yvorvev Lzmxv olhg srh qly zg gsv xlolmb!!"
print answer(s), "Yeah! I can't believe Lance lost his job at the colony!!"