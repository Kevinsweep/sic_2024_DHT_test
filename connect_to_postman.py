from flask import Flask
from flask import request
from flask import jsonify

app = Flask(__name__)
data = []

@app.route('/dataDHT', methods=['POST'])
def post():
    temperature = request.args.get("temperature")
    humidity = request.args.get("humidity")
    subData = {"temperature": temperature, "humidity": humidity}
    
    data.append(subData)
    return 'Data stored in server'

@app.route('/dataDHT', methods=['GET'])
def get():
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
