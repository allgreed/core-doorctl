from flask import Flask, request

app = Flask(__name__)
filepath = 'cards.txt'  

@app.route("/")
def authorize_card():
    """
    Tells if the sent card is allowed 
    """

    current_card = request.args.get('card') 

    with open(filepath) as file:  
        try:
            for line in file:
                one_of_auth_cards = line.split()[0]
                if current_card == one_of_auth_cards:
                    raise AssertionError()
            return "no"
        except AssertionError as exception:
            pass
    return "yes"

# Test endpoints
@app.route("/test/yes")
def yup():
    """
    Afformative
    """

    return "yes"

@app.route("/test/no")
def nope():
    """
    Negative
    """

    return "no"

if __name__ == "__main__":
    app.run(debug=False,host='0.0.0.0')

