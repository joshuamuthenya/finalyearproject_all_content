import requests
import json

# Your Firebase Realtime Database URL (without trailing slash)
url = "https://esp32ldr-32196-default-rtdb.firebaseio.com/ldr.json"

response = requests.get(url)
if response.status_code == 200:
    data = response.json()
    print("All LDR Data:\n")
    print(json.dumps(data, indent=4))
else:
    print("Error fetching data:", response.status_code)

