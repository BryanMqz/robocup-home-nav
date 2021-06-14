import flask
import eventlet
import cv2
import json
from multiprocessing.connection import Listener, Client

from flask import request, jsonify
from flask_socketio import SocketIO, send
from flask_cors import CORS

app = flask.Flask(__name__)
app.config["SCHEDULER_API_ENABLED"] = True
CORS(app)

socketio = SocketIO(app, cors_allowed_origins="*")

# Full duplex connection with the HRI ros node.
receiver_address = ('localhost', 7000)
sender_address = ('localhost', 7001)

ros_receiver = None
ros_sender = None

def initialize_ros_sender():
    global ros_sender
    # Wait to give the ros node time to call its accept method.
    socketio.sleep(1)
    ros_sender = Client(sender_address)
    print("Created ros_sender")

def initialize_ros_receiver():
    global ros_receiver
    ros_receiver_listener = Listener(receiver_address)
    ros_receiver = ros_receiver_listener.accept()

def cleanup():
    ros_sender.close()

    
# Decode messages and send them to the appropriate socket channel.
def ros_receive_handler():
    while True:
        if ros_receiver is None:
            # Avoid blocking the process before initialization.
            socketio.sleep(0.01)
            continue
        # Only call `recv` when we're sure there's a new message since
        # it is a blocking call.
        if ros_receiver.poll():
            try:
                message = ros_receiver.recv()
            except:
                # Ignore message if there was an exception.
                # TODO: We should not do this becuase we could
                # loose critical messages.
                rospy.loginfo("There was an exception")
                continue

            if message == "CreateSender":
                initialize_ros_sender()
            elif message == "Close":
                cleanup()
            else:
                channel = message["channel"]
                value = message["value"]
                socketio.emit(
                    channel,
                    value if type(value) == str else json.dumps(value)
                )
        else:
            # Only throttle if there are no available messages.
            socketio.sleep(0.01)

                
@socketio.on("connect")
def connect_handler():
    print('A user has connected to the server.')

@socketio.on("disconnect")
def disconnect_handler():
    print('A user has disconnected from the server.')

@socketio.on('message')
def handle_message(message):
    print(f"Received message {message}")
    send(message)

@app.errorhandler(404)
def not_found(_):
    return jsonify({"message": "The result was not found"}), 404

@app.route("/", methods=["GET"])
def root():
    socketio.emit("Comm", "Just some message")
    return jsonify({"message": "Welcome to the HOME API"})

@app.route("/stop", methods=["POST"])
def stop_robot():
    global ros_sender
    ros_sender.send("shutdown")
    return jsonify({"message": "Robot was shutdown"})

if __name__ == "__main__":
    # Patch python to make use of an event loop and make background tasks work.
    eventlet.monkey_patch()

    initialize_ros_receiver()
    
    socketio.start_background_task(ros_receive_handler)
    
    # Do not use default port 5000, it might be used by ROS or other os service.
    socketio.run(app, use_reloader=False, port=5050)

