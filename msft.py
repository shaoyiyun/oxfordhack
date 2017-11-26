import requests

import audio

colours = {
    'green' : [0,150,0],
    'yellow' : [250,155,0],
    'blue' : [0,0,150],
    'red' : [150,0,0]
}

def speechToText():

    url = 'https://speech.platform.bing.com/speech/recognition/interactive/cognitiveservices/v1?language=en-GB&format=simple'
	
    data = open(audio.record(), 'rb').read()

    headers = {
        'Ocp-Apim-Subscription-Key': 'e5f16159f94c40f78cc5e720421ea231',
        'Content-type': 'audio/wav; codec=audio/pcm; samplerate=16000'
    }

    res = requests.post(url=url, data=data, headers=headers)
    return getTheColor(res['DisplayText'])
    #return res.json()

def getTheColor(res):
    for key in colours:
        if key in res:
            return colours[key]
    return [256,0,0]

