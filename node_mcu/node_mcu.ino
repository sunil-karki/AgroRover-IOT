#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<SoftwareSerial.h>

SoftwareSerial NodeSerial(D2, D3);  //Rx, Tx

ESP8266WebServer server;
uint8_t pin_led = 16;
//String epass = "started";
//char* ssid = "project-room";
//char* password = "membersonly@acem";

//char* ssid = "khimkarki";
//char* password = "43053DB27F";

//char* ssid = "san";
//char* password = "computer12.3";

char* ssid = "HOME WIFI";
char* password = "home@9851073910";

char floatbuf[32];
float temp_value[22] = {23,45,76,23,4,5,78,34,67,23, 12,23,45,67,78,89,89,45,45,67, 23,25};
float hum_value[22]  = {32,45,76,23,4,5,78,34,67,32, 21,23,45,67,78,90,89,45,45,76, 32,52};
float temp, hum, drill_count, drill_per;
String val_1, val_2, val_3;
bool key = LOW;

void setup()
{
  //Data send to Arduino; pins enable
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);

  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);

  NodeSerial.begin(4800);  // Data out begin
  
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

 // server.on("/",[](){server.send(200,"text/plain","Hello World!");});
   server.on("/", handlerFunc);
  server.on("/weather", weather);
//  server.on("/", handlerFunc);
   server.on("/setting", buttons);
   server.on("/temp", temperature);
  server.on("/hum", humidity);
  server.begin();
}

void loop()
{
  server.handleClient();
  while( NodeSerial.available() )
  {
     if(NodeSerial.read() == '\a')
     {
        val_1 = NodeSerial.readStringUntil('\f');
        val_2 = NodeSerial.readStringUntil('\n');   //temperature
        val_3 = NodeSerial.readStringUntil('\r');   //humidity
        key = HIGH;
     }    
  }   

         if(key == HIGH)
         {
   //           char floatbuf[32]; // make this at least big enough for the whole string
              val_2.toCharArray(floatbuf, sizeof(floatbuf));
              temp = atof(floatbuf);
			  
	//		  char floatbuf1[32]; // make this at least big enough for the whole string
              val_1.toCharArray(floatbuf, sizeof(floatbuf));
              drill_count = atof(floatbuf);
			  drill_per = drill_count/6 *100;

 //             char floatbuf2[32]; // make this at least big enough for the whole string
              val_3.toCharArray(floatbuf, sizeof(floatbuf));
              hum = atof(floatbuf);
              
              for(int i=0; i<=21; i++)
              {
                 if(i==21)
                 {
                    temp_value[i] = temp;
                    hum_value[i] = hum;
                 }
                 else{
                    temp_value[i] = temp_value[i+1];
                    hum_value[i] = hum_value[i+1];
                    }
              }
              key = LOW;
         }
}

void handlerFunc() 
{
   String content = "<html><title>Agro Rover</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\"><link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\"><head>";
   content += "<style>.mySlides {display:none}.w3-left, .w3-right, .w3-badge {cursor:pointer}.w3-badge {height:13px;width:13px;padding:0}ul {    list-style-type: none;    margin: 0;    padding: 0;    overflow: hidden;    background-color: #333;  font-family: \"Calibri\", Times, serif;  font-size: 20px;}li {    float: left;}li a {    display: block;    color: white;    text-align: center;    padding: 14px 16px;    text-decoration: none;}li a:hover:not(.active) {   background-color: #111;}.active {    background-color: #4CAF50;}</style></head><body><ul><li><a  href=\"/\"><img src=\"Icon-Leaves.png\" alt=\"AgroRover\" width=\"40\" height=\"40\"><font size=\"6\" color=\"white\"><sup>&nbsp;AGRO ROVER</sup></font></a></li>  <li><a  href='/'><i style=\"font-size:24px\" class=\"fa\">&#xf015;</i>&nbsp;";
   content += "Home</a></li>  <li><a href='/setting'><i style=\"font-size:24px\" class=\"fa\">&#xf11b;</i>&nbsp;Controls</a></li>  <li><a href='/weather'><i style=\"font-size:24px\" class=\"fa\">&#xf185;</i>&nbsp;Weather</a></li>  <li><a href=\"about.html\"><i style=\"font-size:24px\" class=\"fa\">&#xf05a;</i>&nbsp;About</a></li>  <li><a href=\"help.html\"><i class=\"material-icons\">&#xe8fd;</i>&nbsp;Help</a></li></ul><div class=\"w3-container w3-gray\">";
   content=+ "<div class=\"w3-content w3-display-container\" style=\"max-width:800px\">";
   content += "<img class=\"mySlides\" src= 'https://www.lightwave3d.com/static/media/uploads/gallery_images/landscape_and_nature/tomasz_jaworski-rye.jpg' style=\"width:100%\">  <img class=\"mySlides\" src=\"2.jpg\" style=\"width:100%\">  <img class=\"mySlides\" src=\"4.jpg\" style=\"width:100%\">  <div class=\"w3-center w3-container w3-section w3-large w3-text-white w3-display-bottommiddle\" style=\"width:100%\">    <div class=\"w3-left w3-hover-text-khaki\" onclick=\"plusDivs(-1)\">&#10094;</div> ";
   content += "<div class=\"w3-right w3-hover-text-khaki\" onclick=\"plusDivs(1)\">&#10095;</div>    <span class=\"w3-badge demo w3-border w3-transparent w3-hover-white\" onclick=\"currentDiv(1)\"></span>    <span class=\"w3-badge demo w3-border w3-transparent w3-hover-white\" onclick=\"currentDiv(2)\"></span>    <span class=\"w3-badge demo w3-border w3-transparent w3-hover-white\" onclick=\"currentDiv(3)\"></span>  </div></div></div><script>var slideIndex = 1;showDivs(slideIndex);function plusDivs(n) {  showDivs(slideIndex += n);}function currentDiv(n) {  showDivs(slideIndex = n);}function showDivs(n) {  var i;  var x = document.getElementsByClassName(\"mySlides\"); var dots = document.getElementsByClassName(\"demo\");  if (n > x.length) {slideIndex = 1}  if (n < 1) {slideIndex = x.length}  for (i = 0; i < x.length; i++) {     x[i].style.display = \"none\";    }  for (i = 0; i < dots.length; i++) {     dots[i].className = dots[i].className.replace(\" w3-white\", \"\");  } ";
   content += "x[slideIndex-1].style.display = \"block\";    dots[slideIndex-1].className += \" w3-white\";}</script><footer class=\"w3-container w3-black\">  <h6 style=\"text-align:left;\">Copyright @AgroRover&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
   content += "<i style=\"font-size:24px\" class=\"fa\">&#xf09b;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf230;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf099;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf16d;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf167;</i></h6></footer></body></html>";

   server.send(200, "text/html", content);
   
   server.send(200, "text/html", content);
}

void buttons()
{
   String content = "<html><title>Agro Rover</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\"><link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\"><head><style>ul {    list-style-type: none;    margin: 0;    padding: 0;    overflow: hidden;    background-color: #333; font-family: \"Calibri\", Times, serif;  font-size: 20px;}li {    float: left;}li a {    display: block;    color: white;    text-align: center;    padding: 14px 16px;    text-decoration: none;}li a:hover:not(.active) {    background-color: #111;}.active {    background-color: #4CAF50;}</style></head>";
   content += "<body><ul><li><a  href='/'><img src=\"Icon-Leaves.png\" alt=\"AgroRover\" width=\"40\" height=\"40\"><font size=\"6\" color=\"white\"><sup>&nbsp;AGRO ROVER</sup></font></a></li>";
   content += "<li><a href='/'><i style=\"font-size:24px\" class=\"fa\">&#xf015;</i>&nbsp;Home</a></li><li><a class=\"active\" href=\"/setting\"><i style=\"font-size:24px\" class=\"fa\">&#xf11b;</i>&nbsp;Controls</a></li>  <li><a href='/weather'><i style=\"font-size:24px\" class=\"fa\">&#xf185;</i>&nbsp;Weather</a></li>  <li><a href=\"/\"><i style=\"font-size:24px\" class=\"fa\">&#xf05a;</i>&nbsp;About</a></li>  <li><a href='/'><i class=\"material-icons\">&#xe8fd;</i>&nbsp;Help</a></li></ul><div class=\"w3-container w3-gray\"><div class=\"w3-container\"></p>  <h2><b>MANUAL :</h2></b>  </p><h6>Wheel Control: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;    Other Controls: </h6>";
  // content += " &nbsp;&nbsp;&nbsp;&nbsp;";
   content += "<div class='forms'> <br> <form action='/setting' method='POST'>  <br>";
   content += " &nbsp;&nbsp;&nbsp;&nbsp;<input type= 'submit' name='FORWARD' class=\"w3-button w3-black\" value=\"Forward\">   &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ";
   content += " <input type= 'submit' name= 'DRILLER_GEAR' class=\"w3-button w3-black\" value=\"Driller and Gear\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
   content += " <input type=\"submit\" class=\"w3-button w3-black\" name=\"UPDATE_TEMP\"value=\"Update Weather\"></p>";
   content += " <input type= 'submit' name= 'LEFT' class=\"w3-button w3-black\" value=\"Left\">";
   content += " <input type=\"submit\" name=\"RIGHT\" class=\"w3-button w3-black\" value=\"Right\">  &nbsp;&nbsp;&nbsp;&nbsp; ";
   content += " <input type= 'submit' name= 'STOP' class=\"w3-button w3-black\" value=\"STOP\"> &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
   content += " &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type=\"submit\" class=\"w3-button w3-black\" name=\"SERVO_PIPE\"value=\"Seed\"> &nbsp;&nbsp;&nbsp;&nbsp;";
   content += " <input type= 'submit' name= 'WATER_PIPE' class=\"w3-button w3-black\" value=\"Water\"></p>&nbsp;&nbsp;&nbsp;&nbsp;";
   content += " <input type=\"submit\" class=\"w3-button w3-black\" name=\"BACK\" value=\"Reverse\">   &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
   content += " <input type=\"submit\" class=\"w3-button w3-black\" name=\"SERVO_FLAP_UP\"value=\"Flap-Up\"> &nbsp;&nbsp;&nbsp;&nbsp;";
   content += " <input type=\"submit\" class=\"w3-button w3-black\" name=\"SERVO_FLAP_DOWN\"value=\"Flap-Down\"> ";
   content += " <input type=\"submit\" class=\"w3-button w3-black\" name=\"UPDATE_TEMP\"value=\"Update Weather\">";
   content += "</form></div>";
   
   content += "</p> </div><h2><b>AUTOMATIC :</h2></b></p><div class=\"w3-container\"><i class=\"fa fa-refresh fa-spin\" style=\"font-size:24px\"></i>&nbsp;&nbsp;";
   content += "<input type=\"submit\" class=\"w3-button w3-black\" name= \"START_AUTO\" value=\"AUTO\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ";
   content += " <b>Process Count :";
   content += drill_count; 
   content += "</b><div class=\"w3-light-grey\"></p>  <div class=\"w3-container w3-green w3-center\" style=\"width:";
   content += drill_per;
   content += "%\">loading</div></div></p></div><h6><b>PLEASE NOTE:</b> In case any error occurs which might affect the mechanics of the Rover or anything as such ,unplug the power cable immediately </h6>  </br></div><footer class=\"w3-container w3-black\">  <h6 style=\"text-align:left;\">Copyright @AgroRover&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  <i style=\"font-size:24px\" class=\"fa\">&#xf09b;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf230;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf099;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf16d;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf167;</i></h6></footer></body></html>";

   server.send(200, "text/html", content);


  if (server.hasArg("FORWARD")) 
  {
     NodeSerial.print(10);
     NodeSerial.print("\n");

    server.sendHeader("Location","/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("STOP"))
  {
    NodeSerial.print(20);
    NodeSerial.print("\n");

    server.sendHeader("Location","/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("LEFT"))
  {
    NodeSerial.print(30);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("RIGHT"))
  {
    NodeSerial.print(40);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("BACK"))
  {
    NodeSerial.print(50);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("DRILLER_GEAR"))
  {
    NodeSerial.print(55);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("SERVO_PIPE"))
  {
    NodeSerial.print(60);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("SERVO_FLAP_UP"))
  {
    NodeSerial.print(65);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("SERVO_FLAP_DOWN"))
  {
    NodeSerial.print(67);
    NodeSerial.print("\n");

    server.sendHeader("Location", "/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("WATER_PIPE"))
  {
    NodeSerial.print(70);
    NodeSerial.print("\n");

    server.sendHeader("Location","/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("START_AUTO"))
  {
    NodeSerial.print(5);
    NodeSerial.print("\n");

    server.sendHeader("Location","/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

  if(server.hasArg("UPDATE_TEMP"))
  {
    NodeSerial.print(72);
    NodeSerial.print("\n");

    server.sendHeader("Location","/setting");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

/*  if(server.hasArg("STOP_AUTO"))
  {
    NodeSerial.print(6);
    NodeSerial.print("\n");

    server.sendHeader("Location","/");   //page to 'handlerFunc' func(link to '/')
    server.send(301);
    return;
  }

   */
}

void weather()
{
  
  String content = "<html><title>Agro Rover</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\"><link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">";
  content += "<script src=\"https://www.amcharts.com/lib/3/amcharts.js\"></script><script src=\"https://www.amcharts.com/lib/3/serial.js\"></script><script src=\"https://www.amcharts.com/lib/3/plugins/export/export.min.js\"></script><link rel=\"stylesheet\" href=\"https://www.amcharts.com/lib/3/plugins/export/export.css\" type=\"text/css\" media=\"all\" /><script src=\"https://www.amcharts.com/lib/3/themes/light.js\"></script><head><style> #chartdiv {	width	: 100%;	height	: 390px;	} ";
  content += "table{ border-collapse: collapse;  width: 100%;}th, td { text-align: left; padding: 8px;} tr:nth-child(even){background-color: #f2f2f2} ul { list-style-type: none; margin: 0;  padding: 0;  overflow: hidden;    background-color: #333;  font-family: \"Calibri\", Times, serif;  font-size: 20px;} li { float: left;} li a { display: block; color: white;  text-align: center;    padding: 14px 16px;    text-decoration: none;} li a:hover:not(.active) {  background-color: #111;} .active { background-color: #4CAF50;}</style>";

  content += "</head><body><ul><li><a  href='/'><img src=\"Icon-Leaves.png\" alt=\"AgroRover\" width=\"40\" height=\"40\"><font size=\"6\" color=\"white\"><sup>&nbsp;AGRO ROVER</sup></font></a></li>  <li><a href='/'><i style=\"font-size:24px\" class=\"fa\">&#xf015;</i>&nbsp;Home</a></li>  <li><a  href='/setting'><i style=\"font-size:24px\" class=\"fa\">&#xf11b;</i>&nbsp;Controls</a></li>  <li><a class=\"active\" href='/weather\'><i style=\"font-size:24px\" class=\"fa\">&#xf185;</i>&nbsp;Weather</a></li>  <li><a href='/'><i style=\"font-size:24px\" class=\"fa\">&#xf05a;</i>&nbsp;About</a></li>  <li><a href='/'><i class=\"material-icons\">&#xe8fd;</i>&nbsp;Help</a></li></ul><div class=\"w3-container w3-gray\"><h6><b><font size=\"5\" >Today's weather : </b></font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
  
/*  content += "<button onclick=\"document.getElementById('id02').style.display='block'\" class=\"w3-button w3-black w3-round-xlarge\">Humidity Graph</button>&nbsp; ";
  /*<button onclick=\"do\" class=\"w3-button w3-black w3-round-xlarge\">Temperature Graph</button><div id=\"id01\" class=\"w3-modal\">    <div class=\"w3-modal-content w3-animate-top w3-card-4\">      <header class=\"w3-container w3-green\">         <span onclick=\"document.getElementById('id01').style.display='none'\"         class=\"w3-button w3-display-topright\">&times;</span>        <h2>Temperature Graph: </h2>      </header>      <div class=\"w3-container\"> ";
 content += "<div id=\"chartdiv\"></div></div>";
 content += "<footer class=\"w3-container w3-green\">  <p>Sample temperature</p>  </footer> </div>  </div>  <div id=\"id02\" class=\"w3-modal\">    <div class=\"w3-modal-content w3-animate-top w3-card-4\">      <header class=\"w3-container w3-green\">  <span onclick=\"document.getElementById('id02').style.display='none'\"  class=\"w3-button w3-display-topright\">&times;</span>  <h2>Hum. Graph: </h2> </header>  <div class=\"w3-container\">  <img src=\"temp.png\" alt=\"humidity\" width=\"702\" height=\"232\">  </div> <footer class=\"w3-container w3-green\">  <p>Sample Humidity</p> </footer> </div>  </div>
 */
 content += " <a href=\"/temp\" class=\"w3-button w3-black\">Temperature Graph</a>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
 content += "<a href=\"/hum\" class=\"w3-button w3-black\">Humidity Graph</a></p>";
 content +="<table class=\"w3-table-all\"> <tr class=\"w3-hover-green\">  <td>Condition</td> <td><i style=\"font-size:24px\" class=\"fa\">&#xf0c2;</i></td> <td>Mostly Cloudy</td> </tr> <tr class=\"w3-hover-blue\"> <td>Temperature</td> <td><i style=\"font-size:24px\" class=\"fa\">&#xf2c8;</i></td>  <td>29'C</td></tr><tr class=\"w3-hover-black\"> <td>Humidity</td><td><i class=\"material-icons\">&#xe91c;</i></td><td>2.5</td></tr></table>";
  
  content += "</br><h4><b>Past Week : </b></h4>  <div style=\"overflow-x:auto;\"><table><tr>";
      content+="<th></th>";
      content+="<th>Sunday</th>";
      content+="<th>Monday</th>";
      content+="<th>Tuesday</th>";
      content+="<th>Wednesday</th>";
      content+="<th>Thursday</th>";
      content+="<th>Friday</th>";
      content+="<th>Saturday</th></tr> <tr>";
      content+="<td>Temperature</td>";
      content+="<td>29</td>";
      content+="<td>32</td>";
      content+="<td>26</td>";
      content+="<td>29</td>";
      content+="<td>28</td>";
      content+="<td>33</td>";
      content+="<td>33</td></tr><tr>";
      content+="<td>Humidity</td>";
      content+="<td>32</td>";
      content+="<td>34</td>";
      content+="<td>34</td>";
      content+="<td>32</td>";
      content+="<td>33</td>";
      content+="<td>33</td>";
      content+="<td>33</td></tr> </table></div><h4><b>Past Month : </b></h4>  <div style=\"overflow-x:auto;\">  <table>   <tr>";
      content+="<th></th>";
      content+="<th>Jan</th>";
      content+="<th>Feb</th>";
      content+="<th>Mar</th>";
      content+="<th>April</th>";
      content+="<th>May</th>";
      content+="<th>June</th>";
      content+="<th>July</th>";
       content+="<th>Aug</th>";
      content+="<th>Sept</th>";
     content+="<th>Oct</th>";
      content+="<th>Nov</th>";
       content+="<th>Dec</th></tr><tr>";
      content+="<td>Temperature</td>";
      content+="<td>29</td>";
      content+="<td>29</td>";
      content+="<td>32</td>";
      content+="<td>33</td>";
      content+="<td>33</td>";
      content+="<td>34</td>";
      content+="<td>29</td>";
    content+="<td>29</td>";
      content+="<td>29</td>";
      content+="<td>29</td>";
      content+="<td>29</td>";
      content+="<td>28</td> </tr>    <tr>";
      content+="<td>Humidity</td>";
      content+="<td>32</td>";
      content+="<td>32</td>";
      content+="<td>33</td>";
      content+="<td>34</td>";
      content+="<td>34</td>";
      content+="<td>34</td>";
      content+="<td>32</td>";
    content+="<td>30</td>";
      content+="<td>30</td>";
      content+="<td>30</td>";
      content+="<td>30</td>";
      content+="<td>32</td>";
      
    content += "</tr></table></div></p><footer class=\"w3-container w3-black\">  <h6 style=\"text-align:left;\">Copyright @AgroRover&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  <i style=\"font-size:24px\" class=\"fa\">&#xf09b;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf230;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf099;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf16d;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf167;</i></h6></footer>";
  
/*  content += "<script>var chart = AmCharts.makeChart(\"chartdiv\", {\"type\": \"serial\",\"theme\": \"light\",\"marginRight\": 40,\"marginLeft\": 40,\"autoMarginOffset\": 20,\"mouseWheelZoomEnabled\":true,\"dataDateFormat\": \"YYYY-MM-DD\",\"valueAxes\": [{\"id\": \"v1\",\"axisAlpha\": 0,\"position\": \"left\",\"ignoreAxisWidth\":true}],";
   content += " \"balloon\": {\"borderThickness\": 1,\"shadowAlpha\": 0},";
   content += " \"graphs\": [{\"id\": \"g1\",\"balloon\":{\"drop\":true,\"adjustBorderColor\":false,\"color\":\"#ffffff\"},";
   content += " \"bullet\": \"round\",\"bulletBorderAlpha\": 1,\"bulletColor\": \"#FFFFFF\",\"bulletSize\": 5,\"hideBulletsCount\": 50,\"lineThickness\": 2,\"title\": \"red line\",\"useLineColorForBulletBorder\": true,\"valueField\": \"value\",}],";
   content += " \"chartScrollbar\": {\"graph\": \"g1\",\"oppositeAxis\":false,\"offset\":30,\"scrollbarHeight\": 80,\"backgroundAlpha\": 0,\"selectedBackgroundAlpha\": 0.1,\"selectedBackgroundColor\": \"#888888\",\"graphFillAlpha\": 0,\"graphLineAlpha\": 0.5,\"selectedGraphFillAlpha\": 0,\"selectedGraphLineAlpha\": 1,\"autoGridCount\":true,\"color\":\"#AAAAAA\"},";
   content += " \"chartCursor\": {\"pan\": true,\"valueLineEnabled\": true,\"valueLineBalloonEnabled\": true,\"cursorAlpha\":1,\"cursorColor\":\"#258cbb\",\"limitToGraph\":\"g1\",\"valueLineAlpha\":0.2,\"valueZoomable\":true},";
   content += " \"valueScrollbar\":{\"oppositeAxis\":false,\"offset\":50,\"scrollbarHeight\":10},\"categoryField\": \"date\",\"categoryAxis\": {\"parseDates\": true,\"dashLength\": 1,\"minorGridEnabled\": true},";
   content += " \"export\": {\"enabled\": true},";

   
   content += " \"dataProvider\": [ {\"date\": \"2012-11-01\",\"value\":"; content+= temp_value[0]; content+= "}, {\"date\": \"2012-11-02\",\"value\":"; content+= temp_value[1]; content+= "}, {\"date\": \"2012-11-03\",\"value\":"; content+= temp_value[2]; content+= "}, {\"date\": \"2012-11-04\",\"value\":"; content+= temp_value[3]; content+= "}, {\"date\": \"2012-11-05\",\"value\":"; content+= temp_value[4]; content+= "}, {\"date\": \"2012-11-06\",\"value\":";
   content += temp_value[5]; content+= "}, {\"date\": \"2012-11-07\",\"value\":"; content+= temp_value[6]; content+= "},";
   content += " {\"date\": \"2012-11-08\",\"value\":"; content+= temp_value[7]; content+= "}, {\"date\": \"2012-11-09\",\"value\":"; content+= temp_value[8]; content+= "}, {\"date\": \"2012-11-10\",\"value\":"; content+= temp_value[9]; content+= "}, {\"date\": \"2012-11-11\",\"value\":"; content+= temp_value[10]; content+= "}, {\"date\": \"2012-11-12\",\"value\":"; content+= temp_value[11]; content+= "}, {\"date\": \"2012-11-13\",\"value\":"; 
   content += temp_value[12]; content+= "}, {\"date\": \"2012-11-14\",\"value\":"; content+= temp_value[13]; content+= "},";
   content += " {\"date\": \"2012-11-15\",\"value\":"; content+= temp_value[14]; content+= "}, {\"date\": \"2012-11-16\",\"value\":"; content+= temp_value[15]; content+= "}, {\"date\": \"2012-11-17\",\"value\":"; content+= temp_value[16]; content+= "}, {\"date\": \"2012-11-18\",\"value\":"; content+= temp_value[17]; content+= "}, {\"date\": \"2012-11-19\",\"value\":"; content+= temp_value[18]; content+= "}, {\"date\": \"2012-11-20\",\"value\":";
   content += temp_value[19]; content+= "}, {\"date\": \"2012-11-21\",\"value\":"; content+= temp_value[20]; content+= "},";
   
   
   content += " {\"date\": \"2012-11-22\",\"value\":"; content+= temp_value[21];
   content += " }, ]});  chart.addListener(\"rendered\", zoomChart);  zoomChart();";

   content += "function zoomChart() {chart.zoomToIndexes(chart.dataProvider.length - 40, chart.dataProvider.length - 1);}";
   content += "</script>";
  */
    
   content += "</body></html>";

 server.send(200, "text/html", content);
 
      server.send(200, "text/html", content);
}

void temperature()
{

/* String content = "<html><title>Agro Rover</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\"><link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\" rel=\"stylesheet\">";
 
   content = "<script src=\"https://www.amcharts.com/lib/3/amcharts.js\"></script>";
   content += "<script src=\"https://www.amcharts.com/lib/3/serial.js\"></script><script src=\"https://www.amcharts.com/lib/3/plugins/export/export.min.js\"></script>";
   content += "<link rel=\"stylesheet\" href=\"https://www.amcharts.com/lib/3/plugins/export/export.css\" type=\"text/css\" media=\"all\" />";
   content += "<script src=\"https://www.amcharts.com/lib/3/themes/light.js\"></script>";
   content+="<head><style>ul {    list-style-type: none;    margin: 0;    padding: 0;    overflow: hidden;    background-color: #333; font-family: \"Calibri\", Times, serif;  font-size: 20px;}li {    float: left;}li a {    display: block;    color: white;    text-align: center;    padding: 14px 16px;    text-decoration: none;}li a:hover:not(.active) {    background-color: #111;}.active {    background-color: #4CAF50;}</style></head>";
   content += "<body><ul><li><a  href='/'><img src=\"Icon-Leaves.png\" alt=\"AgroRover\" width=\"40\" height=\"40\"><font size=\"6\" color=\"white\"><sup>&nbsp;AGRO ROVER</sup></font></a></li>";
   content += "<li><a href='/'><i style=\"font-size:24px\" class=\"fa\">&#xf015;</i>&nbsp;Home</a></li><li><a class=\"active\" href=\"/setting\"><i style=\"font-size:24px\" class=\"fa\">&#xf11b;</i>&nbsp;Controls</a></li>  <li><a href='/weather'><i style=\"font-size:24px\" class=\"fa\">&#xf185;</i>&nbsp;Weather</a></li>  <li><a href=\"/\"><i style=\"font-size:24px\" class=\"fa\">&#xf05a;</i>&nbsp;About</a></li>  <li><a href='/'><i class=\"material-icons\">&#xe8fd;</i>&nbsp;Help</a></li></ul><div class=\"w3-container w3-gray\"><div class=\"w3-container\"></p>  <h2><b>TEMPEATURE GRAPH :</h2></b>  </p>";

  
     content += "<script>var chart = AmCharts.makeChart(\"chartdiv\", {\"type\": \"serial\",\"theme\": \"light\",\"marginRight\": 40,\"marginLeft\": 40,\"autoMarginOffset\": 20,\"mouseWheelZoomEnabled\":true,\"dataDateFormat\": \"YYYY-MM-DD\",\"valueAxes\": [{\"id\": \"v1\",\"axisAlpha\": 0,\"position\": \"left\",\"ignoreAxisWidth\":true}],";
   content += " \"balloon\": {\"borderThickness\": 1,\"shadowAlpha\": 0},";
   content += " \"graphs\": [{\"id\": \"g1\",\"balloon\":{\"drop\":true,\"adjustBorderColor\":false,\"color\":\"#ffffff\"},";
   content += " \"bullet\": \"round\",\"bulletBorderAlpha\": 1,\"bulletColor\": \"#FFFFFF\",\"bulletSize\": 5,\"hideBulletsCount\": 50,\"lineThickness\": 2,\"title\": \"red line\",\"useLineColorForBulletBorder\": true,\"valueField\": \"value\",}],";
   content += " \"chartScrollbar\": {\"graph\": \"g1\",\"oppositeAxis\":false,\"offset\":30,\"scrollbarHeight\": 80,\"backgroundAlpha\": 0,\"selectedBackgroundAlpha\": 0.1,\"selectedBackgroundColor\": \"#888888\",\"graphFillAlpha\": 0,\"graphLineAlpha\": 0.5,\"selectedGraphFillAlpha\": 0,\"selectedGraphLineAlpha\": 1,\"autoGridCount\":true,\"color\":\"#AAAAAA\"},";
   content += " \"chartCursor\": {\"pan\": true,\"valueLineEnabled\": true,\"valueLineBalloonEnabled\": true,\"cursorAlpha\":1,\"cursorColor\":\"#258cbb\",\"limitToGraph\":\"g1\",\"valueLineAlpha\":0.2,\"valueZoomable\":true},";
   content += " \"valueScrollbar\":{\"oppositeAxis\":false,\"offset\":50,\"scrollbarHeight\":10},\"categoryField\": \"date\",\"categoryAxis\": {\"parseDates\": true,\"dashLength\": 1,\"minorGridEnabled\": true},";
   content += " \"export\": {\"enabled\": true},";

   
   content += " \"dataProvider\": [ {\"date\": \"2012-11-01\",\"value\":"; content+= temp_value[0]; content+= "}, {\"date\": \"2012-11-02\",\"value\":"; content+= temp_value[1]; content+= "}, {\"date\": \"2012-11-03\",\"value\":"; content+= temp_value[2]; content+= "}, {\"date\": \"2012-11-04\",\"value\":"; content+= temp_value[3]; content+= "}, {\"date\": \"2012-11-05\",\"value\":"; content+= temp_value[4]; content+= "}, {\"date\": \"2012-11-06\",\"value\":";
   content += temp_value[5]; content+= "}, {\"date\": \"2012-11-07\",\"value\":"; content+= temp_value[6]; content+= "},";
   content += " {\"date\": \"2012-11-08\",\"value\":"; content+= temp_value[7]; content+= "}, {\"date\": \"2012-11-09\",\"value\":"; content+= temp_value[8]; content+= "}, {\"date\": \"2012-11-10\",\"value\":"; content+= temp_value[9]; content+= "}, {\"date\": \"2012-11-11\",\"value\":"; content+= temp_value[10]; content+= "}, {\"date\": \"2012-11-12\",\"value\":"; content+= temp_value[11]; content+= "}, {\"date\": \"2012-11-13\",\"value\":"; 
   content += temp_value[12]; content+= "}, {\"date\": \"2012-11-14\",\"value\":"; content+= temp_value[13]; content+= "},";
   content += " {\"date\": \"2012-11-15\",\"value\":"; content+= temp_value[14]; content+= "}, {\"date\": \"2012-11-16\",\"value\":"; content+= temp_value[15]; content+= "}, {\"date\": \"2012-11-17\",\"value\":"; content+= temp_value[16]; content+= "}, {\"date\": \"2012-11-18\",\"value\":"; content+= temp_value[17]; content+= "}, {\"date\": \"2012-11-19\",\"value\":"; content+= temp_value[18]; content+= "}, {\"date\": \"2012-11-20\",\"value\":";
   content += temp_value[19]; content+= "}, {\"date\": \"2012-11-21\",\"value\":"; content+= temp_value[20]; content+= "},";
   
   
   content += " {\"date\": \"2012-11-22\",\"value\":"; content+= temp_value[21];
   content += " }, ]});  chart.addListener(\"rendered\", zoomChart);  zoomChart();";

   content += "function zoomChart() {chart.zoomToIndexes(chart.dataProvider.length - 40, chart.dataProvider.length - 1);}";


   
   content += "</script>";
   
   
   content +="<div id='chartdiv'></div></p> <h6> Figure: Temperature Graph </h6> <style>#chartdiv { width : 100%; height : 500px;}</style>";
   
     
   content += "  <footer class=\"w3-container w3-black\">  <h6 style=\"text-align:left;\">Copyright @AgroRover&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
   content += "<i style=\"font-size:24px\" class=\"fa\">&#xf09b;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf230;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf099;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf16d;</i> <i style=\"font-size:24px\" class=\"fa\">&#xf167;</i></h6></footer>";
   
content += "</body></html>";
*/

String content = "<html><head><title>robot.....</title><script src=\"https://www.amcharts.com/lib/3/amcharts.js\"></script>";
   content += "<script src=\"https://www.amcharts.com/lib/3/serial.js\"></script><script src=\"https://www.amcharts.com/lib/3/plugins/export/export.min.js\"></script>";
   content += "<link rel=\"stylesheet\" href=\"https://www.amcharts.com/lib/3/plugins/export/export.css\" type=\"text/css\" media=\"all\" />";
   content += "<script src=\"https://www.amcharts.com/lib/3/themes/light.js\"></script>";

   content += "<script>var chart = AmCharts.makeChart(\"chartdiv\", {\"type\": \"serial\",\"theme\": \"light\",\"marginRight\": 40,\"marginLeft\": 40,\"autoMarginOffset\": 20,\"mouseWheelZoomEnabled\":true,\"dataDateFormat\": \"YYYY-MM-DD\",\"valueAxes\": [{\"id\": \"v1\",\"axisAlpha\": 0,\"position\": \"left\",\"ignoreAxisWidth\":true}],";
   content += " \"balloon\": {\"borderThickness\": 1,\"shadowAlpha\": 0},";
   content += " \"graphs\": [{\"id\": \"g1\",\"balloon\":{\"drop\":true,\"adjustBorderColor\":false,\"color\":\"#ffffff\"},";
   content += " \"bullet\": \"round\",\"bulletBorderAlpha\": 1,\"bulletColor\": \"#FFFFFF\",\"bulletSize\": 5,\"hideBulletsCount\": 50,\"lineThickness\": 2,\"title\": \"red line\",\"useLineColorForBulletBorder\": true,\"valueField\": \"value\",}],";
   content += " \"chartScrollbar\": {\"graph\": \"g1\",\"oppositeAxis\":false,\"offset\":30,\"scrollbarHeight\": 80,\"backgroundAlpha\": 0,\"selectedBackgroundAlpha\": 0.1,\"selectedBackgroundColor\": \"#888888\",\"graphFillAlpha\": 0,\"graphLineAlpha\": 0.5,\"selectedGraphFillAlpha\": 0,\"selectedGraphLineAlpha\": 1,\"autoGridCount\":true,\"color\":\"#AAAAAA\"},";
   content += " \"chartCursor\": {\"pan\": true,\"valueLineEnabled\": true,\"valueLineBalloonEnabled\": true,\"cursorAlpha\":1,\"cursorColor\":\"#258cbb\",\"limitToGraph\":\"g1\",\"valueLineAlpha\":0.2,\"valueZoomable\":true},";
   content += " \"valueScrollbar\":{\"oppositeAxis\":false,\"offset\":50,\"scrollbarHeight\":10},\"categoryField\": \"date\",\"categoryAxis\": {\"parseDates\": true,\"dashLength\": 1,\"minorGridEnabled\": true},";
   content += " \"export\": {\"enabled\": true},";

   
   content += " \"dataProvider\": [ {\"date\": \"2012-11-01\",\"value\":"; content+= temp_value[0]; content+= "}, {\"date\": \"2012-11-02\",\"value\":"; content+= temp_value[1]; content+= "}, {\"date\": \"2012-11-03\",\"value\":"; content+= temp_value[2]; content+= "}, {\"date\": \"2012-11-04\",\"value\":"; content+= temp_value[3]; content+= "}, {\"date\": \"2012-11-05\",\"value\":"; content+= temp_value[4]; content+= "}, {\"date\": \"2012-11-06\",\"value\":";
   content += temp_value[5]; content+= "}, {\"date\": \"2012-11-07\",\"value\":"; content+= temp_value[6]; content+= "},";
   content += " {\"date\": \"2012-11-08\",\"value\":"; content+= temp_value[7]; content+= "}, {\"date\": \"2012-11-09\",\"value\":"; content+= temp_value[8]; content+= "}, {\"date\": \"2012-11-10\",\"value\":"; content+= temp_value[9]; content+= "}, {\"date\": \"2012-11-11\",\"value\":"; content+= temp_value[10]; content+= "}, {\"date\": \"2012-11-12\",\"value\":"; content+= temp_value[11]; content+= "}, {\"date\": \"2012-11-13\",\"value\":"; 
   content += temp_value[12]; content+= "}, {\"date\": \"2012-11-14\",\"value\":"; content+= temp_value[13]; content+= "},";
   content += " {\"date\": \"2012-11-15\",\"value\":"; content+= temp_value[14]; content+= "}, {\"date\": \"2012-11-16\",\"value\":"; content+= temp_value[15]; content+= "}, {\"date\": \"2012-11-17\",\"value\":"; content+= temp_value[16]; content+= "}, {\"date\": \"2012-11-18\",\"value\":"; content+= temp_value[17]; content+= "}, {\"date\": \"2012-11-19\",\"value\":"; content+= temp_value[18]; content+= "}, {\"date\": \"2012-11-20\",\"value\":";
   content += temp_value[19]; content+= "}, {\"date\": \"2012-11-21\",\"value\":"; content+= temp_value[20]; content+= "},";
   
   
   content += " {\"date\": \"2012-11-22\",\"value\":"; content+= temp_value[21];
   content += " }, ]});  chart.addListener(\"rendered\", zoomChart);  zoomChart();";

   content += "function zoomChart() {chart.zoomToIndexes(chart.dataProvider.length - 40, chart.dataProvider.length - 1);}";
   content += "</script></head><body><div id='chartdiv'></div><p>hello</p><style>#chartdiv { width : 100%; height : 500px;}</style></body></html>";

      server.send(200, "text/html", content);

}

void humidity()
{
   String content = "<html><head><title>robot.....</title><script src=\"https://www.amcharts.com/lib/3/amcharts.js\"></script>";
   content += "<script src=\"https://www.amcharts.com/lib/3/serial.js\"></script><script src=\"https://www.amcharts.com/lib/3/plugins/export/export.min.js\"></script>";
   content += "<link rel=\"stylesheet\" href=\"https://www.amcharts.com/lib/3/plugins/export/export.css\" type=\"text/css\" media=\"all\" />";
   content += "<script src=\"https://www.amcharts.com/lib/3/themes/light.js\"></script>";

   content += "<script>var chart = AmCharts.makeChart(\"chartdiv\", {\"type\": \"serial\",\"theme\": \"light\",\"marginRight\": 40,\"marginLeft\": 40,\"autoMarginOffset\": 20,\"mouseWheelZoomEnabled\":true,\"dataDateFormat\": \"YYYY-MM-DD\",\"valueAxes\": [{\"id\": \"v1\",\"axisAlpha\": 0,\"position\": \"left\",\"ignoreAxisWidth\":true}],";
   content += " \"balloon\": {\"borderThickness\": 1,\"shadowAlpha\": 0},";
   content += " \"graphs\": [{\"id\": \"g1\",\"balloon\":{\"drop\":true,\"adjustBorderColor\":false,\"color\":\"#ffffff\"},";
   content += " \"bullet\": \"round\",\"bulletBorderAlpha\": 1,\"bulletColor\": \"#FFFFFF\",\"bulletSize\": 5,\"hideBulletsCount\": 50,\"lineThickness\": 2,\"title\": \"red line\",\"useLineColorForBulletBorder\": true,\"valueField\": \"value\",}],";
   content += " \"chartScrollbar\": {\"graph\": \"g1\",\"oppositeAxis\":false,\"offset\":30,\"scrollbarHeight\": 80,\"backgroundAlpha\": 0,\"selectedBackgroundAlpha\": 0.1,\"selectedBackgroundColor\": \"#888888\",\"graphFillAlpha\": 0,\"graphLineAlpha\": 0.5,\"selectedGraphFillAlpha\": 0,\"selectedGraphLineAlpha\": 1,\"autoGridCount\":true,\"color\":\"#AAAAAA\"},";
   content += " \"chartCursor\": {\"pan\": true,\"valueLineEnabled\": true,\"valueLineBalloonEnabled\": true,\"cursorAlpha\":1,\"cursorColor\":\"#258cbb\",\"limitToGraph\":\"g1\",\"valueLineAlpha\":0.2,\"valueZoomable\":true},";
   content += " \"valueScrollbar\":{\"oppositeAxis\":false,\"offset\":50,\"scrollbarHeight\":10},\"categoryField\": \"date\",\"categoryAxis\": {\"parseDates\": true,\"dashLength\": 1,\"minorGridEnabled\": true},";
   content += " \"export\": {\"enabled\": true},";

   
   content += " \"dataProvider\": [ {\"date\": \"2012-11-01\",\"value\":"; content+= hum_value[0]; content+= "}, {\"date\": \"2012-11-02\",\"value\":"; content+= hum_value[1]; content+= "}, {\"date\": \"2012-11-03\",\"value\":"; content+= hum_value[2]; content+= "}, {\"date\": \"2012-11-04\",\"value\":"; content+= hum_value[3]; content+= "}, {\"date\": \"2012-11-05\",\"value\":"; content+= hum_value[4]; content+= "}, {\"date\": \"2012-11-06\",\"value\":";
   content += hum_value[5]; content+= "}, {\"date\": \"2012-11-07\",\"value\":"; content+= hum_value[6]; content+= "},";
   content += " {\"date\": \"2012-11-08\",\"value\":"; content+= hum_value[7]; content+= "}, {\"date\": \"2012-11-09\",\"value\":"; content+= hum_value[8]; content+= "}, {\"date\": \"2012-11-10\",\"value\":"; content+= hum_value[9]; content+= "}, {\"date\": \"2012-11-11\",\"value\":"; content+= hum_value[10]; content+= "}, {\"date\": \"2012-11-12\",\"value\":"; content+= hum_value[11]; content+= "}, {\"date\": \"2012-11-13\",\"value\":"; 
   content += hum_value[12]; content+= "}, {\"date\": \"2012-11-14\",\"value\":"; content+= hum_value[13]; content+= "},";
   content += " {\"date\": \"2012-11-15\",\"value\":"; content+= hum_value[14]; content+= "}, {\"date\": \"2012-11-16\",\"value\":"; content+= hum_value[15]; content+= "}, {\"date\": \"2012-11-17\",\"value\":"; content+= hum_value[16]; content+= "}, {\"date\": \"2012-11-18\",\"value\":"; content+= hum_value[17]; content+= "}, {\"date\": \"2012-11-19\",\"value\":"; content+= hum_value[18]; content+= "}, {\"date\": \"2012-11-20\",\"value\":";
   content += hum_value[19]; content+= "}, {\"date\": \"2012-11-21\",\"value\":"; content+= hum_value[20]; content+= "},";
   
   
   content += " {\"date\": \"2012-11-22\",\"value\":"; content+= hum_value[21];
   content += " }, ]});  chart.addListener(\"rendered\", zoomChart);  zoomChart();";

   content += "function zoomChart() {chart.zoomToIndexes(chart.dataProvider.length - 40, chart.dataProvider.length - 1);}";
   content += "</script></head><body><div id='chartdiv'></div><p>hello</p><style>#chartdiv { width : 100%; height : 500px;}</style></body></html>";

      server.send(200, "text/html", content);
}

