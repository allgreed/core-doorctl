FROM python:3-alpine

COPY requirements.txt /tmp/
RUN pip3 install -r /tmp/requirements.txt

COPY . /service
WORKDIR /service

EXPOSE 5000
CMD ["python3", "main.py"]
