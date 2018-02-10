# core-doorctl
Hackserspace door control system via RFID cards

## System "architecture"

The doorctl system consist of:
- server handling card authentication
- microcontroller operating the door and reading RFID cards

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

- Python server that stores the cards in a text file
- Reponds to requests with card number with either 0 or 1

- Devboard reading card number
- Devboard running servo
- Devboard making requests
- Devboard sending card number to server and opening door based on the response

### Initial:

- Server logs request to logfile
- Dockerized server with instruction (cards via data volume)
- Run on HS infrastructure

- ESP from devboard to production!

### Improvements:

- Move ESP credentials from code to memory
    - Add a program to upload them

- Encrypt communication between device and server
- Authenticate the server and the device
- System handles more than 1 door

