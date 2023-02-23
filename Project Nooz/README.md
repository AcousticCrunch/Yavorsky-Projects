# Project Nooz

## Configurations
- SSH and SSHD configurations are found in /etc/ssh
- Nginx configurations are found in /etc/nginx as well as /etc/sites-enabled
- Gunicorn configurations are found in /etc/systemd/system
- Our DNS configuration is located on Cloudflare

[DNS Configuration](https://i.imgur.com/97Qc5d6.png)

## How do we update/upgrade the server?

We have deliberately turned off auto-updates and upgrades in our Ubuntu-based server. This way, we have consistency with the versions of the various applications we use.

If we need to add a python library, or update a current one, we have implemented a virtual python enviroment that controls the library versions seperate from our local versions.

For everything outside of python, we use sudo apt install, which we have also disabled auto-updates for in the config file for apt.

## How a cURL Request Works

cURL utilizes many protocols such as HTTP(s) / FTP and many others to communicate to a server using a URL. Using the HTTP method, most common 
requests are GET, POST, PUT and DELETE. 

[Illustration of HTTP](https://www3.ntu.edu.sg/home/ehchua/programming/webprogramming/images/TheWeb.png)

HTTP is layered over TCP to transport its message data. TCP itself, is layered over IP.

For a request there is a request message and the response from the server includes a start line, a header and a body. Start line specifies what HTTP does regarding the website. Header includes the constraints or formatting for the data. The body is the response that a server sends back.


Regarding HTTP, curl works by:
1. Curl recognizes the HTTP request from the URL
2. Sends a request to the server, getting the IP from the DNS server of the URL
3. Sends a HTTP request with the start line to the specified IP. Example below:

    GET /index.html HTTP/1.1
    Host: www.example.com
        
4. Server responds with its own HTTP response with the content and metadata. 

    HTTP/1.1 200 OK

5. A browser would then render that response. cURL displays only the content such as the start line, header, and body. Other information can be specified by using flags such as:
    --head

    HTTP uses port 80 on the server's IP to communicate these messages.

    HTTPs is similar but uses an assymetric encryption to encrypt the messages between the client / server and uses port 443. Additional    verification occurs from the certificate of the web server. 

    When we do
    curl projectNooz.me

    We get:
    [image](https://i.imgur.com/Tv9gLP9.png)


## How flask executes Python code

Nginx uses Flask to serve python code. Nginx acts as a main middleman to reading / sending data. We configure Nginx to grab web app files in the location {} block in the configuration file. Gunicorn acts as the middle man between flask and nginx. The Flask application gets sent to nginx through Gunicorn. The data is sent as the https body to the client by Nginx. 

## Security for Project Nooz

Intruders can't access our server because we are using a secure way to SSH into it. We are using a private key, shared among us in a secure manner (Slack messages). This is a secure symmetric encryption.

We have only certain ports opened in our virtual machine such as 22 for SSH and 443 for HTTPs communication. We are only using HTTPs for sending and retrieving data with a cloudflare DNS and SSL certificate. Our firewall also allows only HTTPs as well. 

We are also using Microsoft Azure to host our website. This limits the risk of hardware tampering.

## How to make this server yourself

Below are the steps we followed to create our server to host projectNooz:

Step 1: Use local server hardware or a cloud server to provide the hardware for the server.

Step 2: Install Ubuntu Server 20.04 on your server of choice.

Step 3: Use this article to setup nginx on your Ubuntu server.
https://www.digitalocean.com/community/tutorials/how-to-install-nginx-on-ubuntu-20-04

Step 4: Use this article to setup gunicorn and flask on your Ubuntu server. Also adds SSL certification to your website.
https://www.digitalocean.com/community/tutorials/how-to-serve-flask-applications-with-gunicorn-and-nginx-on-ubuntu-22-04

Step 5: Create an account on Auth0's website and follow this quick start guide to setup authentication in flask.
https://auth0.com/docs/quickstart/webapp/python/01-login
