# core-doorctl
Hackserspace door control system via RFID cards

## System "architecture"

The doorctl system consist of:
- server handling card authentication
- microcontroller operating the door and reading RFID cards

## Communication

- Device sends GET request to server @5000 with query parameter "card" containing comma separated card number, eg. ```3,06,4,40,2,45,106,921,265,7```
- Example dev URL: ```http://localhost:5000/?card=3,06,4,40,2,45,106,921,265,7```
- Server responds with "yes" if the card is authorized, "no" otherwise

## Development

### Server

#### Instalation

```sh
    virtualenv env
    . env/bin/activate
    pip3 install flask
```

#### Usage

```sh
    python3 main.py
```

## TODO:

### POC:

- Devboard reading card number
- Devboard running servo
- Devboard making requests
- Devboard sending card number to server and opening door based on the response

### Initial:

- Server logs request to logfile -> person or card id
- Dockerized server with instruction
- Run on HS infrastructure

- ESP from devboard to production!

### Improvements:

- Card list and log via Docker volume so that cards can be added without image rebuilds
- Move ESP credentials from code to memory
    - Add a program to upload them

- Encrypt communication between device and server
- Authenticate the server and the device
- System handles more than 1 door
- Don't authorize cards via their fucking ID...

#### Probbably like never:

- Do a CLI for manual door control for authorized users
- Integrate with Hs master auth

