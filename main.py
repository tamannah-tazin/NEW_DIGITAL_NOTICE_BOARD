import os
import smtplib
from email.message import EmailMessage
import Email_Sender as config   

NOTICES_FOLDER = "notices"

def send_notice_email(txt_file_path):
    with open(txt_file_path, 'rb') as f:
        file_data = f.read()
        file_name = os.path.basename(txt_file_path)

    msg = EmailMessage()
    msg['From'] = config.SENDER_EMAIL
    msg['To'] = ", ".join(config.RECEIVER_EMAILS)
    msg['Subject'] = config.SUBJECT
    msg.set_content(config.BODY)

    msg.add_attachment(file_data, maintype='text', subtype='plain', filename=file_name)

    try:
        with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:
            server.login(config.SENDER_EMAIL, config.SENDER_PASSWORD)
            server.send_message(msg)
        print(f"✅ Email has been send successfully : {file_name}")
    except Exception as e:
        print(f"❌ Email hasn't send successfully: {e}")

def main():
    for filename in os.listdir(NOTICES_FOLDER):
        if filename.endswith('.txt'):
            txt_path = os.path.join(NOTICES_FOLDER, filename)
            send_notice_email(txt_path)

if __name__ == "__main__":
    main()
