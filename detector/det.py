"""
File: det.py
Author: Atman
Date: 12/26/25
Description:
    
"""

from ultralytics import YOLO
import argparse
import os
import cv2


if __name__ == "__main__":
    # ch dir
    # os.chdir(os.path.dirname(os.path.abspath(__file__)))
    # parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--image_path", type=str, required=True, help="Path to the image to compress")
    parser.add_argument("--label", type=str, required=True, help= "Label of the object to detect")
    args = parser.parse_args()
    image_path = args.image_path
    label = args.label
    # inference
    model = YOLO("yolov8n.pt")
    result = model(image_path, conf=0.4)[0]
    names = model.names          # dict: id -> name
    label_id = [k for k, v in names.items() if v == label][0]

    bboxes = result.boxes.xyxy
    scores = result.boxes.conf
    labels = result.boxes.cls
    # save crops
    img = cv2.imread(image_path)
    os.makedirs('./crops', exist_ok=True)
    for i, (bbox, cls, score) in enumerate(zip(bboxes, labels, scores)):
        if int(cls) != label_id:
            continue
        x1, y1, x2, y2 = map(int, bbox.tolist())
        crop = img[y1:y2, x1:x2]
        print(f"save ./crops/{label}_{i}_{score:.2f}.jpg")
        save_path = f'./crops/{label}_{i}_{score:.2f}.jpg'
        cv2.imwrite(save_path, crop)
    print("extract end")
