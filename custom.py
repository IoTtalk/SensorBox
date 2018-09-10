import DAN

ServerIP = 'http://IP:9999' # or = 'https://DomainName' 
Comm_interval = 15 # unit:second

def profile_init():
    DAN.profile['dm_name']='SensorBox'
    DAN.profile['d_name']= 'Sensor' #DAN.profile['dm_name']+'.'+DAN.get_mac_addr()[-4:]

def odf():  # int only
    return []

def idf():
    return [
       ('AtPressure', float),
       ('Bugs', int),
       ('Humidity', float),
       ('Moisture1', float),
       ('pH1', float),
       ('Temperature', float),
       ('UV1', float),
       ('UV2', float),
    ]
