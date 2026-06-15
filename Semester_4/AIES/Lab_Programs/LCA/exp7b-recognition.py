import face_recognition
import cv2

known_image = face_recognition.load_image_file("known.jpg")
known_encoding = face_recognition.face_encodings(known_image)[0]

known_faces = [known_encoding]
known_names = ["Person1"]

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    rgb = frame[:, :, ::-1]

    faces = face_recognition.face_locations(rgb)
    encodings = face_recognition.face_encodings(rgb, faces)

    for (top, right, bottom, left), face_encoding in zip(faces, encodings):

        matches = face_recognition.compare_faces(known_faces, face_encoding)

        name = "Unknown"

        if True in matches:
            name = known_names[0]

        # draw box + name
        cv2.rectangle(frame, (left, top), (right, bottom), (0,255,0), 2)
        cv2.putText(frame, name, (left, top-10),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0,255,0), 2)

    cv2.imshow("Face Recognition", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()