"""
Simple script that grabs new news stories from hackernews. Triggers every hour
"""

from hackernews import HackerNews
import sqlite3
import datetime

hn = HackerNews()

try:
  # Connect to database and create cursor
    con = sqlite3.connect("/home/azureuser/projectNooz/news.db")
    cur = con.cursor()
    print("Database created and Successfully Connected to SQLite")
  
  # Get data from top 50 news stories on hackernews and insert into database
    for ts in hn.top_stories(limit=50):
        data_tuple = (ts.item_id, ts.title, ts.url, ts.by, ts.submission_time)
        cur.execute(
            "INSERT INTO topStories(news_id, title, url, user, submission_date) VALUES (?, ?, ?, ?, ?);",
            data_tuple,
        )
   # Commit to database
        con.commit()

except sqlite3.Error as error:
    print("Error with sqlite operations:", error)

finally:
    if con:
      
        # Delete stories older than 2 days
        cur.execute(
            "DELETE FROM topStories WHERE submission_date <= date('now', '-2 day');"
        )
        
        # Commit to database and close connection
        con.commit()
        con.close()
        print("The SQLite connection is closed")
