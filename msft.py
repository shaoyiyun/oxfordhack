import requests

import audio

def speechToText():

	url = 'https://speech.platform.bing.com/speech/recognition/interactive/cognitiveservices/v1?language=en-GB&format=simple'

	data = open(audio.record(), 'rb').read()

	headers = {
		'Ocp-Apim-Subscription-Key': 'e5f16159f94c40f78cc5e720421ea231',
		'Content-type': 'audio/wav; codec=audio/pcm; samplerate=16000'
	}

	res = requests.post(url=url, data=data, headers=headers)

	return res.json()
