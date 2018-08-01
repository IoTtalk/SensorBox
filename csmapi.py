import requests

ENDPOINT = None
TIMEOUT=10
IoTtalk = requests.Session()


class CSMError(Exception):
    pass

def register(mac_addr, profile):
    r = IoTtalk.post(
        ENDPOINT + '/' + mac_addr,
        json={'profile': profile}, timeout=TIMEOUT
    )
    if r.status_code != 200: raise CSMError(r.text)
    return True


def deregister(mac_addr):
    r = IoTtalk.delete(ENDPOINT + '/' + mac_addr)
    if r.status_code != 200: raise CSMError(r.text)
    return True


def push(mac_addr, df_name, data):
    r = IoTtalk.put(
        ENDPOINT + '/' + mac_addr + '/' + df_name,
        json={'data': data}, timeout=TIMEOUT
    )
    if r.status_code != 200: raise CSMError(r.text)
    return True


def pull(mac_addr, df_name):
    r = IoTtalk.get(ENDPOINT + '/' + mac_addr + '/' + df_name, timeout=TIMEOUT)
    if r.status_code != 200: raise CSMError(r.text)
    return r.json()['samples']


def tree():
    r = IoTtalk.get(ENDPOINT + '/tree')
    if r.status_code != 200: raise CSMError(r.text)
    return r.json()
