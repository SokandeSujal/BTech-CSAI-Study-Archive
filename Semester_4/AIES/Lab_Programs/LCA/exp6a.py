# Simple Chatbot

def chatbot():
    print("Chatbot started (type 'bye' to exit)")

    while True:
        user = input("You: ").lower()

        # exit
        if user == "bye":
            print("Bot: Goodbye!")
            break

        # FAQ (rule-based)
        elif user == "what is your name":
            print("Bot: I am a chatbot")

        elif user == "how are you":
            print("Bot: I am fine")

        elif user == "what can you do":
            print("Bot: I can answer simple questions")

        # keyword matching
        elif "hello" in user or "hi" in user:
            print("Bot: Hello!")

        elif "college" in user:
            print("Bot: Which college are you in?")

        elif "exam" in user:
            print("Bot: Study well and do your best!")

        elif "help" in user:
            print("Bot: I am here to help you")

        else:
            print("Bot: Sorry, I don't understand")

# run chatbot
chatbot()