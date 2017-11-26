import requests

import audio

colours = {
    'oxford blue' : [0,33,71],
    'green' : [0,150,0],
    'yellow' : [250,155,0],
    'blue' : [0,0,150],
    'red' : [150,0,0],
    'pink' : [255,192,203],
    'violet' : [238,130,238],
    'indigo' : [75,0,130],
    'mint' : [189,252,201],
    'gold' : [255,215,0],
    'orange' : [255,128,0]
}

def speechToText():

    url = 'https://speech.platform.bing.com/speech/recognition/interactive/cognitiveservices/v1?language=en-GB&format=simple'
	
    data = open(audio.record(), 'rb').read()

    headers = {
        'Ocp-Apim-Subscription-Key': 'e5f16159f94c40f78cc5e720421ea231',
        'Content-type': 'audio/wav; codec=audio/pcm; samplerate=16000'
    }

    res = requests.post(url=url, data=data, headers=headers)
    print(res.json())
    text = res.json()['DisplayText'].lower()
    if reset(text):
        return [-1]
    if setRainbow(text):
        return [1] #mode for rainbow
    c = getTheColor(text)
    if c != []:
        return c
    f = setFlash(text)
    if f != -1:
        return [3,f]
    l = setLevel(text)
    if l != -1:
        return [4,l]
    sl = setStartFlash(text)
    if sl != -1:
        return [5,sl]
    return []
    #return res.json()

def getTheColor(res):
    for key in colours:
        if key in res:
            return colours[key]
    return []

def setRainbow(res):
    if 'rainbow' in res:
            return True
    return False

def reset(res):
    if 'reset' in res:
        return True
    return False


def setFlash(res) :
    if 'flash' in res:
        if 'stop' in res:
            return 2
        elif 'slow' in res:
            return 0
        else :
            return 1
    return -1

def setLevel(res) :
    if 'set ' in res:
        if 'sound' in res:
            if 'high' in res:
                return 4
            else:
                return 5
    return -1

def setStartFlash(res):
    if 'set ' in res:
        if 'start' in res and  'flash' in res :
            newlevel = text2int(res)
            return newlevel
    return -1

def text2int(textnum, numwords={}):
    if not numwords:
      units = [
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
        "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
        "sixteen", "seventeen", "eighteen", "nineteen",
      ]

      tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

      scales = ["hundred", "thousand", "million", "billion", "trillion"]

      numwords["and"] = (1, 0)
      for idx, word in enumerate(units):    numwords[word] = (1, idx)
      for idx, word in enumerate(tens):     numwords[word] = (1, idx * 10)
      for idx, word in enumerate(scales):   numwords[word] = (10 ** (idx * 3 or 2), 0)

    current = result = 0
    for word in textnum.split():
        if word in numwords:

            scale, increment = numwords[word]
            current = current * scale + increment
            if scale > 100:
                result += current
                current = 0

    return result + current

