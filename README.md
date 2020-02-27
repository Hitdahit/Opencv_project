# Opencv_project
---
* I'll upload (opencv tutorial code + comments) and my project using opencv.
## Lane Recognition Project
* This project will be written with C++. and you should use hsv_ransac_ver-0.cpp.
* rest of cpp files are my trial and errors, so i don't recommand you to use them.
* this project's strategy is using lane's color(which is typically white and yellow) transformed to hsvColor.
* after i croped lane's points with color strategy, I will use ransac algorithm.

check original img and result img.
* gather lane's points 

![image](https://user-images.githubusercontent.com/42925197/75315771-fa936300-58a6-11ea-90f9-56c6a9d05825.png)

* left_lane ransac

![image](https://user-images.githubusercontent.com/42925197/75315692-bacc7b80-58a6-11ea-929f-c536cb8aed2a.png)

* full ransac and find_route to drive through

![image](https://user-images.githubusercontent.com/42925197/75315790-0848e880-58a7-11ea-9373-e495643f28e4.png)
  * caution: you may be need to edit roi function's vertices array in _.cpp, reason followed under this line.
  #### ransac malfunctions if input img contains strange object which is not road.   (but it typially works.)
  
  * like these errors
  
   ![image](https://user-images.githubusercontent.com/42925197/75437233-41618580-5999-11ea-8924-8f26efc1472b.png)
   ![image](https://user-images.githubusercontent.com/42925197/75442945-cbaee700-59a3-11ea-829e-93762d4a1ace.png)

  * This program's input is still img. I will revise it so this project use video as a input.
  * hsv_ransac_ver-0.cpp will be refactorzied soon.
  - change format to class to make code more shorter.
  - it has two version of ransac(1차함수, 3차함수) and choose one of them by c_max value, but i will chage it soon.
     * so among those two error, i corrected second one so far...
     
     ![image](https://user-images.githubusercontent.com/42925197/75443203-3eb85d80-59a4-11ea-866f-14905a56ae8b.png)

---
## Open_YOLO Project summary
* I will construct YOLO network in C++, to make object detector in video files.

* Not only this, but also I will check my model's throughput and measure workloads.
  * I want to study about Real Time Issue in object detection Problem. This is why I'm doing this project.

    ### Here is sample image of my project.
    ![Screenshot from 2020-01-24 23-35-22](https://user-images.githubusercontent.com/42925197/73077399-70508b80-3f03-11ea-85fa-f2a6351760d5.png)

---



