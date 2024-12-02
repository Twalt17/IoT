# import paho.mqtt as mqtt
import paho.mqtt.client as mqtt
import mysql.connector

HOST = "2a02:4780:b:969:0:1021:2863:3"  # Replace with your Hostinger database IP
USER = "u270608483_db_TylerWalter"    # Replace with your database username
PASSWORD = "2XEwWDG/u_Qf(GG" # Replace with your database password
DATABASE = "u270608483_TylerWalters" # Replace with your database name

# Define the MQTT broker and topic
BROKER_URL = "broker.mqtt-dashboard.com"  # Public HiveMQ broker
BROKER_PORT = 8000               # WebSocket port
TOPIC = "testtopic/temp/outTopic/voltage"   # Topic to subscribe to

def push_value_to_db(sensor_value):
   try:
       # Connect to the database
       connection = mysql.connector.connect(
           host=HOST,
           user=USER,
           password=PASSWORD,
           database=DATABASE
       )


       if connection.is_connected():
           print("Connected to the database!")


           # Create a cursor object
           cursor = connection.cursor()


           # SQL query to insert data
           insert_query = "INSERT INTO sensor_value (value) VALUES (%s)"
           cursor.execute(insert_query, (sensor_value,))


           # Commit the transaction
           connection.commit()
           print(f"Value {sensor_value} inserted into sensor_value table!")


   except mysql.connector.Error as err:
       print(f"Error: {err}")
   finally:
    if connection.is_connected():
           cursor.close()
           connection.close()
           print("Database connection closed.")

# Define callback for connection
def on_connect(client, userdata, flags, rc):
   if rc == 0:
       print("Connected to HiveMQ broker!")
       # Subscribe to the topic once connected
       client.subscribe(TOPIC)
       print(f"Subscribed to topic: {TOPIC}")
   else:
       print(f"Failed to connect, return code {rc}")


# Define callback for receiving messages
def on_message(client, userdata, msg):
   print(f"Received message: {msg.payload.decode()} from topic: {msg.topic}")
   message = msg.payload.decode() 
   try:
        # Convert the message to a float if it's a sensor value
        sensor_value = float(message)
        push_value_to_db(sensor_value)  # Push the value to the database
   except ValueError:
        print(f"Invalid sensor value: {message}")  # Handle non-numeric payloads

# Create an MQTT client instance
client = mqtt.Client(transport="websockets")


# Attach callback functions
client.on_connect = on_connect
client.on_message = on_message


# Connect to the HiveMQ broker
print("Connecting to broker...")
client.connect(BROKER_URL, BROKER_PORT, 60)


# Start the MQTT client loop
client.loop_forever()
