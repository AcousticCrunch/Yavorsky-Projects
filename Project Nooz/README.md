# Project Nooz

## Configurations
- SSH and SSHD configurations are found in /etc/ssh
- Nginx configurations are found in /etc/nginx as well as /etc/sites-enabled
- Gunicorn configurations are found in /etc/systemd/system
- Our DNS configuration is located on Cloudflare

[DNS Configuration](https://i.imgur.com/97Qc5d6.png)

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
