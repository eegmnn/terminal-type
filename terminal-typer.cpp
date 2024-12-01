#include <ncurses.h>
#include <string>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <sstream>

// Function prototypes
void initialize_ncurses();
void terminate_ncurses();
void initialize_colors();
std::string get_random_test_string(const std::vector<std::string>& passages);
void display_timer(double remaining_time);
void display_passage_lines(const std::vector<std::string>& lines, size_t top_line_index, size_t char_index);
std::vector<std::string> split_string_by_word(const std::string& str, size_t max_line_length);
size_t find_current_word_start(const std::string& line, size_t char_index);
void highlight_word(const std::string& line, size_t start_index, size_t end_index, int row, int col);
void display_user_input(const std::string& user_input, const std::string& test_string, size_t start_index);
void run_typing_test(const std::vector<std::string>& passages);

// Constants
const double TIME_LIMIT = 60.0; // seconds
const int INPUT_ROW = 12;       
const int INPUT_COL = 2;
const int LINE_WIDTH = 60;      // Maximum width of each line for both the test string and user input

int main() {
    // Initialize ncurses
    initialize_ncurses();
    initialize_colors();

    // Test Passages
    std::vector<std::string> passages = {
        "The forest was vast and filled with secrets waiting to be discovered. As the young explorer walked deeper into the woods, the sunlight filtering through the leaves created dappled patterns on the forest floor. Birds chirped, and the gentle rustling of the leaves in the wind added to the sense of adventure. He had heard stories about the hidden lake that lay beyond the hills, where the water shimmered like silver and the air smelled like fresh pine. No one from his village had seen it in years, and many doubted its existence. But he was determined to find it, not only for the challenge but also for the thrill of discovering something truly magical.",
        "The universe is an expansive and mysterious entity, vast beyond human comprehension. It is filled with billions of galaxies, each containing billions of stars. As we gaze up at the night sky, we are reminded that we are just a tiny part of a much larger cosmos. There are wonders we have yet to discover, planets yet to be visited, and phenomena we can barely begin to understand. From swirling galaxies millions of light-years away to the black holes that defy the laws of physics, our universe is both awe-inspiring and humbling. The more we learn about space, the more we realize just how much remains unknown.",
        "Hard work and perseverance are the foundation of all success stories. The journey to success is rarely straightforward; it is filled with challenges, obstacles, and setbacks. However, those who succeed are the ones who get back up after every fall, who learn from their failures, and who keep going even when things get tough. It's important to remember that every great achievement started with a simple idea, nurtured by consistent effort and relentless dedication. Talent can take you far, but perseverance and hard work can take you even farther. Remember, it's not the destination but the journey that truly matters.",
        "We live in an age of technology, where information is just a click away. The rise of the internet has changed the way we interact, communicate, and even think. Social media platforms keep us connected to friends and family no matter where they are in the world. We have access to almost limitless knowledge, and yet, we are often overwhelmed by it. The challenge today is not only finding information but discerning which sources to trust and how to use that information responsibly. Technology can empower us, but it also requires us to be careful about what we share, consume, and believe.",
        "Long ago, there was a kingdom hidden among the mountains, covered in mist and magic. It was said that the kingdom thrived on the laughter of its people and the wisdom of its leaders. The rivers flowed with crystal-clear water, and the valleys were lush with flowers of every color imaginable. However, as generations passed, greed and mistrust began to creep into the hearts of the rulers. They lost sight of what made their kingdom great, and the once-happy land fell into darkness. The people left, the laughter faded, and the magic disappeared. Legends say that one day, someone with a pure heart will come to restore the kingdom to its former glory.",
        "Nature has always been the greatest artist. The vibrant colors of a sunset, the intricate patterns of a spider's web, the delicate petals of a rose—all of these are masterpieces created without human intervention. As we go about our busy lives, it's easy to forget to stop and appreciate the beauty around us. The rustling of leaves in the wind, the rhythmic sound of ocean waves crashing against the shore, or the stillness of a snow-covered morning can bring a sense of peace that is hard to find elsewhere. Nature has a way of reminding us of what truly matters and bringing us back to a place of tranquility.",
        "Innovation is the driving force of human progress. Throughout history, humanity has faced countless challenges, and each time, we have found ways to overcome them. The future is being shaped by the incredible advancements we are making today. Technologies like artificial intelligence, renewable energy, and biotechnology are poised to change our world in ways we can only begin to imagine. Self-driving cars, intelligent robots, and space travel are no longer just concepts from science fiction; they are becoming a reality. The future holds endless possibilities, and it is our creativity and determination that will shape what it looks like.",
        "There is something magical about opening a book and diving into its pages. A good story can transport you to distant lands, introduce you to characters who feel like friends, and leave you with a sense of wonder that lasts long after you've read the final page. Reading is an escape, a journey into the mind of another person, an opportunity to live a thousand lives. Whether it's fiction or non-fiction, fantasy or history, each book has a unique story to tell, and each one has the potential to change the way you see the world. There is no greater joy than getting lost in a book that speaks to your heart.",
        "The human spirit is resilient, capable of withstanding hardships and emerging even stronger. Throughout history, people have faced adversities of all kinds—wars, natural disasters, personal losses—but have found ways to persevere. It is in our nature to fight, to hold on, and to hope for a better tomorrow. No matter how challenging the situation, there is always something within us that refuses to give up. It's this resilience that has brought about change, that has turned despair into triumph, and that reminds us, time and time again, that we are stronger than we think.",
        "Curiosity is at the heart of every discovery, every invention, every advancement that has ever been made. It is the desire to understand, to learn, to know more. As children, we ask countless questions about the world—why the sky is blue, how planes fly, what makes rain. But as we grow older, we sometimes lose that sense of wonder. The greatest minds in history—Einstein, Da Vinci, Curie—were all driven by an insatiable curiosity that led them to question the status quo and explore the unknown. In a world that often tells us to accept things as they are, curiosity is what pushes us to make things better.",
        "Every morning brings a new beginning, a new chance to make a difference, to grow, to change. The possibilities are endless, and it is up to us to choose which direction to take. Life is full of unexpected twists and turns, and sometimes it can be daunting not knowing what comes next. But it is also exhilarating, knowing that we have the power to shape our future. Every decision we make, every action we take, brings us closer to who we want to become. The journey might not always be easy, but it is always worth it.",
        "Traveling opens up the world in a way nothing else can. It allows you to see different cultures, taste exotic foods, and meet people whose lives are vastly different from your own. It teaches you that despite our differences, there is a common thread that unites us all—the desire for happiness, the need for connection, the pursuit of dreams. Whether you are exploring the bustling streets of Tokyo, hiking through the Andes, or sailing in the Mediterranean, travel has a way of expanding your perspective and reminding you of the beauty and diversity of the world we live in.",
        "The sun was setting beyond the horizon, painting the sky with vibrant hues of red, orange, and purple. The village below was slowly being enveloped by the evening shadows, and the first stars began to peek through the darkening sky. There was something magical about watching the day end, as if the world were pausing for a moment to reflect on all that had happened. People in the village were finishing their chores, children were playing in the fading light, and a gentle breeze carried the scent of freshly baked bread from a nearby house. The world felt peaceful, and everything seemed to be in its rightful place.",
        "On a small farm nestled between two hills, lived a family who cherished the simple things in life. The mornings started with the crowing of the rooster and the sound of animals stirring in the barn. There was a rhythm to their days that brought comfort and stability. They would work the fields under the golden sun, tending to crops that would feed not only themselves but also their neighbors. In the evenings, they would gather around the kitchen table, sharing stories of the day and laughing together. It was a life without luxury, but one rich in love, connection, and gratitude.",
        "The library was an escape, a portal to other worlds, other times, other lives. It was a place where silence was cherished, where the rustling of pages was the only sound that echoed between the towering shelves. The old librarian, with her half-moon glasses and kind smile, watched over the readers as they got lost in the stories they held in their hands. She knew the power of books, the way a well-told story could transport someone to places they had never dreamed of visiting. And every time she saw someone sitting, engrossed in a book, she knew they had discovered the magic too.",
        "In the depths of the ocean, where the sunlight could not reach, strange and wonderful creatures lived. There were fish with bodies that glowed in the dark, jellyfish that floated like ethereal spirits, and giant squid that moved silently through the water. It was a world that was as alien as it was beautiful, filled with creatures that had adapted in remarkable ways to survive in such an inhospitable environment. The ocean was mysterious, hiding secrets that humans were still striving to uncover. It was a reminder of just how vast and unknown our planet still is.",
        "The rain tapped gently against the window, a rhythmic sound that brought a sense of calm to the otherwise busy household. It was a Sunday afternoon, the kind that invited you to curl up with a book and a warm blanket. The world outside was gray, with puddles forming in the streets and raindrops trickling down the glass. Inside, there was warmth—a fire crackling in the fireplace, the smell of cookies baking in the oven, and the soft murmur of conversation. It was one of those moments where everything felt right, where time seemed to slow down just enough to appreciate the beauty in the ordinary.",
        "The old clock tower stood at the center of the town, a relic of a bygone era. Its hands moved slowly, marking the passage of time with a soft ticking that was barely audible over the hustle and bustle of daily life. The townspeople rarely paid it any attention, but to those who took the time to look, it was a reminder that time marched on, regardless of the joys or troubles of the day. The clock had seen the town change over the years—buildings had come and gone, people had grown up and moved away, and yet, the clock remained, steadfast in its duty to keep time for everyone.",
        "Once upon a time, in a land covered with emerald forests and sparkling lakes, there lived a young princess who had no interest in the life of luxury that surrounded her. Instead, she longed for adventure, for the thrill of discovering the unknown. She would sneak out of the castle at night, her footsteps silent against the stone floors, and wander through the forest under the moonlight. There, she would meet the creatures of the night—owls, foxes, and even a wolf who had become her friend. They shared in her adventures, exploring hidden groves and secret paths that no one else knew.",
        "It was the first snowfall of the year, and the world was transformed into a winter wonderland. The trees were covered in a blanket of white, their branches bending slightly under the weight of the snow. The air was crisp, and every breath left a cloud of mist in the cold. Children ran outside, their laughter ringing through the air as they made snow angels and built snowmen. The whole town seemed to slow down, as if the snow had brought a sense of tranquility that made everything feel softer, quieter. It was a beautiful moment, one that made people pause and appreciate the simple joys of winter.",
        "The desert stretched as far as the eye could see, an endless expanse of golden sand that shimmered under the blazing sun. There were dunes that rose and fell like waves in a vast ocean, and the wind carved intricate patterns on the surface of the sand. It was a harsh, unforgiving landscape, but there was beauty in its simplicity. At night, the desert came alive under the stars, the sky a deep black canvas dotted with countless points of light. It was a reminder of just how small we are in the grand scheme of things, but also of how connected we are to the universe around us.",
        "In the heart of the bustling city, there was a small park that offered a quiet escape from the noise and chaos of urban life. Tall trees provided shade, their leaves rustling softly in the breeze. There were benches where people could sit and read, paths where children rode their bicycles, and a small pond where ducks swam lazily. It was a place where people came to find a moment of peace, to reconnect with nature in the midst of the concrete jungle. The city might have been loud and busy, but in the park, time seemed to slow down, and everything felt just a little bit lighter.",
        "Music has a way of touching the soul, of expressing emotions that words often fail to capture. The right melody can bring tears to your eyes, make your heart swell with joy, or transport you to a distant memory. There are songs that speak to the deepest parts of us, that make us feel understood and less alone. Whether it's the gentle strumming of an acoustic guitar, the powerful notes of a symphony, or the rhythmic beat of a drum, music has the power to connect us to ourselves and to others. It transcends language, culture, and borders, reminding us of our shared humanity.",
        "The lighthouse stood tall at the edge of the rocky coast, its light sweeping across the dark waters to guide ships safely to shore. It had weathered countless storms, its sturdy walls bearing the marks of time and the elements. To the sailors out at sea, the lighthouse was a beacon of hope, a sign that they were not alone in the vastness of the ocean. It represented safety, resilience, and the promise of a safe harbor. Even in the darkest nights, when the waves crashed violently against the rocks, the light continued to shine, unwavering and constant.",
        "The invention of flight changed the world in ways that early dreamers like Da Vinci could hardly imagine. What began as a dream of soaring like birds has led to an age where people can travel across the globe in a matter of hours. The first planes were fragile, clumsy machines, yet they opened the skies and ignited imaginations. Today, planes connect people, cultures, and countries, shrinking the vastness of our world. Airports are like gateways to adventure, and the thrill of taking off into the sky never quite goes away. Flight reminds us that the impossible can become reality.",
        "The mountains loomed in the distance, their peaks covered in snow even in the warmth of summer. They were majestic, standing tall and proud against the blue sky. To climb them was a challenge, but also a calling for those who sought adventure and the thrill of reaching the summit. The journey up the mountain was difficult—steep trails, rocky paths, and unpredictable weather tested the strength and determination of the climbers. But those who made it to the top were rewarded with a view that took their breath away. It was a reminder that the best things in life often come after the hardest climbs.",
        "The world is full of stories—some true, some imagined, and some somewhere in between. Every person has a story to tell, shaped by their experiences, dreams, and fears. Stories have the power to inspire, to comfort, to educate, and to connect. They allow us to see the world through someone else's eyes, to walk in their shoes for a while, and to understand things we may have never experienced ourselves. Whether told around a campfire, written in a book, or shared through a movie, stories are what make us human. They remind us that we are not alone, that we are all part of something greater.",
        "The wind howled through the trees, bending branches and scattering leaves in every direction. The night was dark, with thick clouds obscuring the moon, casting everything in shadow. Somewhere in the distance, a wolf let out a lone, haunting howl, the sound echoing across the vast wilderness. The old cabin stood at the edge of the clearing, its windows rattling from the force of the wind. Inside, the fire flickered, casting long shadows across the wooden floor. It was a night that made you want to huddle under a blanket, away from the world outside, and wait for the storm to pass.",
        "The marketplace was alive with energy, colors, and sounds. Stalls of fresh fruits and vegetables lined the pathways, their bright colors drawing the attention of passersby. Vendors called out to potential customers, their voices blending with the chatter of the crowd and the clinking of coins. The air was rich with the smells of freshly baked bread, spices, and sizzling street food. Children ran between the stalls, laughing and playing, while adults haggled over prices. It was a place where people came together, where the heart of the town beat strongest, and where the simple acts of buying and selling became something much more.",
        "A gentle mist hung over the valley as the first rays of sunlight pierced through the treetops. The world seemed to hold its breath in the early morning light, the dew shimmering on the grass like tiny jewels. Birds began to sing, their calls echoing through the stillness, bringing the valley to life. In the distance, a river flowed quietly, its surface reflecting the sky above. A lone deer stepped out of the woods, pausing to drink from the cool water. It was a moment untouched by time, a reminder of the beauty and peace that existed in the world, waiting to be noticed by those who took the time to look.",
        "The space station orbited Earth in silence, a tiny metal construct in the vastness of space. Below, the planet spun, covered in swirls of white clouds and expanses of deep blue ocean. The astronauts aboard were weightless, floating gently from one module to another, working on experiments that would one day benefit all of humanity. It was a strange feeling to be so far from the surface, to look out the window and see home as a distant sphere. But it was also humbling—a reminder of how small our world was in the vastness of the universe, and yet how precious it was, a fragile blue jewel in an endless sea of stars.",
        "The city was alive, even at midnight. Lights glowed in the windows of skyscrapers, cars rushed down the streets, and people moved about, heading to late-night cafes or coming home from long shifts. There was an energy that could only be felt in a city at night—an energy that was both electric and calming. The neon signs blinked, reflecting off wet pavement, and the sound of distant music mixed with the hum of traffic. Somewhere, a couple sat on a park bench, sharing a quiet moment in the chaos, while someone else stood by a street corner, looking out at the cityscape and feeling both alone and part of something larger.",
        "The inventor's workshop was cluttered with half-finished gadgets, wires, and blueprints scattered across every available surface. It was a place of chaos, but to the inventor, it was also a place of potential. Every tool had its purpose, every pile of parts held the possibility of something new. Today, he was working on a device that he hoped would change the world. He adjusted his goggles, carefully connecting wires and gears, his hands moving with practiced precision. He knew that most of his inventions would fail—that was part of the process—but he also knew that one day, something would work, and it would all be worth it.",
        "The waves crashed against the cliffs, sending salty spray into the air. The lighthouse stood tall on the edge of the rocky coast, its beam of light cutting through the darkness. The night was stormy, the wind howling as if it carried the voices of a thousand lost sailors. The keeper of the lighthouse, an old man with weathered hands and a kind smile, watched the storm from the safety of his small room. He had seen many storms in his time, but each one reminded him of the power of the sea and the importance of his duty. His light was the only thing standing between safety and disaster for the ships that ventured too close to the dangerous coast.",
        "The meadow was a sea of wildflowers, their bright colors painting the landscape in shades of red, yellow, and blue. Bees buzzed lazily from one blossom to another, and butterflies danced in the warm summer breeze. In the distance, a small creek wound its way through the grass, its waters sparkling in the sunlight. It was the kind of day that made you want to lie down in the grass, close your eyes, and let the warmth of the sun wash over you. Time seemed to slow down, the worries of the world fading away, replaced by the simple joy of being surrounded by beauty and nature.",
        "The cat sat in the window, its golden eyes watching the world outside. It was a rainy day, and the streets were empty, save for the occasional car driving by, its tires splashing through puddles. The cat's tail twitched as it followed the movement of a lone bird hopping along the wet sidewalk. Inside the house, everything was warm and dry, a sharp contrast to the dreary day outside. The cat liked the rain, though—it was calming, the rhythmic sound of droplets tapping against the glass, the way the world seemed softer, quieter. It made the cat feel safe, watching the rain from its cozy perch.",
    };

    bool replay = true;

    while (replay) {
        run_typing_test(passages);

        // Wait for user input to replay or quit
        while (true) {
            int ch = getch();
            if (ch == 'r' || ch == 'R') {
                replay = true;
                break; // Restart the loop to replay
            } else if (ch == 27 || ch == 'q' || ch == 'Q') {
                replay = false;
                break; // Exit the program
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    // Terminate ncurses
    terminate_ncurses();
    return 0;
}

void run_typing_test(const std::vector<std::string>& passages) {
    std::string test_string = get_random_test_string(passages);

    std::vector<std::string> passage_lines = split_string_by_word(test_string, LINE_WIDTH);
    std::string user_input = "";
    size_t index = 0;
    size_t top_line_index = 0;  // Index of the top line in the passage_lines vector
    size_t user_input_start = 0; // Start index for visible user input (for scrolling)
    bool test_completed = false;
    bool exited = false;
    bool timer_started = false;

    // Clear screen and display instructions
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(1, 2, "Welcome to the Typing Test!");
    mvprintw(2, 2, "Type the following text as quickly and accurately as you can.");
    mvprintw(3, 2, "Press ESC to exit at any time.");
    attroff(COLOR_PAIR(4));

    // Display initial passage (two lines) with highlighted current word
    mvprintw(5, 2, "Test String:");
    display_passage_lines(passage_lines, top_line_index, index);

    // Display User Input prompt
    mvprintw(INPUT_ROW - 1, 2, "Your Input:");
    display_user_input(user_input, test_string, user_input_start);
    move(INPUT_ROW, INPUT_COL); // Move cursor to input line

    refresh();

    auto start_time = std::chrono::steady_clock::now();
    while (!test_completed && !exited) {
        auto current_time = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = current_time - start_time;
        double elapsed_seconds = elapsed.count();

        double remaining_time = TIME_LIMIT - elapsed_seconds;

        // Update timer display if timer has started
        if (timer_started) {
            if (remaining_time >= 0) {
                display_timer(remaining_time);
            }

            if (remaining_time <= 0) {
                break; // Time's up
            }
        }

        // Get user input
        int ch = getch();

        // Start the timer, if not started already and valid char input received
        if (!timer_started && (ch >= 32 && ch <= 126)) {
            timer_started = true;
            start_time = std::chrono::steady_clock::now();
            remaining_time = TIME_LIMIT - 0.0;
            display_timer(remaining_time);
        }

        if (ch == 27) { // ESC
            exited = true;
            break;
        } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) { // Backspace/Delete
            if (!user_input.empty()) {
                user_input.pop_back();
                index--;

                // Update start index for scrolling if needed
                if (index < user_input_start) {
                    user_input_start = (user_input_start > 0) ? user_input_start - 1 : 0;
                }

                // Update the displayed user input
                display_user_input(user_input, test_string, user_input_start);
                display_passage_lines(passage_lines, top_line_index, index);
            }
        } else if (ch >= 32 && ch <= 126) { // Valid printable characters
            if (index < test_string.length()) {
                char expected_char = test_string[index];
                char input_char = static_cast<char>(ch);
                user_input += input_char;

                // Update scrolling window if necessary
                if (user_input.length() > LINE_WIDTH) {
                    user_input_start++;
                }

                // Update the displayed user input with color coding
                display_user_input(user_input, test_string, user_input_start);

                index++;

                // Update the passage display with the new index to highlight corresponding word
                display_passage_lines(passage_lines, top_line_index, index);

                // Check if top line is completed and update lines if necessary
                if (index >= (top_line_index + 1) * LINE_WIDTH) {
                    top_line_index++;
                }

                // Check if test is completed
                if (index >= test_string.length()) {
                    test_completed = true;
                }
            }
        }

        // Small delay to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        refresh();
    }

    // End timing
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> total_elapsed = end_time - start_time;
    double time_taken = total_elapsed.count(); // In seconds

    // Calculate WPM and Accuracy
    // Ensure we use the actual time taken, not exceeding TIME_LIMIT
    if (time_taken > TIME_LIMIT) {
        time_taken = TIME_LIMIT;
    }

    double wpm = (user_input.length() / 5.0) / (time_taken / 60.0);

    int correct_chars = 0;
    for (size_t i = 0; i < user_input.length() && i < test_string.length(); ++i) {
        if (user_input[i] == test_string[i]) {
            correct_chars++;
        }
    }
    double accuracy = (static_cast<double>(correct_chars) / test_string.length()) * 100.0;

    // Display results
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(2, 2, "Test Completed!");
    attroff(COLOR_PAIR(4));

    mvprintw(4, 4, "Time taken: %.2f seconds", time_taken);
    mvprintw(5, 4, "Words per minute (WPM): %.2f", wpm);
    mvprintw(6, 4, "Accuracy: %.2f%%", accuracy);
    mvprintw(8, 2, "Press 'R' to replay or 'Q'/'ESC' to exit.");
    refresh();
}


void display_passage_lines(const std::vector<std::string>& lines, size_t top_line_index, size_t char_index) {
    // Display two lines, starting from top_line_index
    std::string top_line = (top_line_index < lines.size()) ? lines[top_line_index] : "";
    std::string bottom_line = (top_line_index + 1 < lines.size()) ? lines[top_line_index + 1] : "";

    // Clear the previous lines to avoid leftover characters
    mvprintw(6, 2, "%-60s", " ");
    mvprintw(7, 2, "%-60s", " ");

    // Determine which line the current character falls on
    size_t current_line_start_index = top_line_index * LINE_WIDTH;
    std::string current_line = top_line;

    if (char_index >= current_line_start_index + LINE_WIDTH) {
        current_line = bottom_line;
        current_line_start_index += LINE_WIDTH;
    }

    // Find the start and end of the current word based on the character index
    size_t relative_char_index = char_index - current_line_start_index;
    size_t current_word_start = find_current_word_start(current_line, relative_char_index);
    size_t current_word_end = current_line.find(' ', current_word_start);
    if (current_word_end == std::string::npos) {
        current_word_end = current_line.length();
    }

    // Print top line with current word highlighted by changing its background
    for (size_t i = 0; i < top_line.length(); ++i) {
        if (top_line_index == current_line_start_index / LINE_WIDTH && i >= current_word_start && i < current_word_end) {
            attron(COLOR_PAIR(5)); // Background highlight for the current word
        }
        mvaddch(6, 2 + i, top_line[i]);
        if (i == current_word_end - 1) {
            attroff(COLOR_PAIR(5));
        }
    }

    // Print bottom line
    mvprintw(7, 2, "%s", bottom_line.c_str());
}

std::vector<std::string> split_string_by_word(const std::string& str, size_t max_line_length) {
    std::vector<std::string> lines;
    std::istringstream iss(str);
    std::string word;
    std::string current_line;

    while (iss >> word) {
        if (current_line.length() + word.length() + 1 > max_line_length) {
            lines.push_back(current_line);
            current_line = word;
        } else {
            if (!current_line.empty()) {
                current_line += " ";
            }
            current_line += word;
        }
    }
    if (!current_line.empty()) {
        lines.push_back(current_line);
    }

    return lines;
}

size_t find_current_word_start(const std::string& line, size_t char_index) {
    // Find the start of the current word by looking for the previous space
    if (char_index >= line.length()) {
        return line.length();
    }

    if (char_index == 0 || line[char_index] == ' ') {
        return char_index;
    }

    size_t start = line.rfind(' ', char_index);
    if (start == std::string::npos) {
        return 0;
    }
    return start + 1;
}

void highlight_word(const std::string& line, size_t start_index, size_t end_index, int row, int col) {
    // Highlight word with different background color
    attron(COLOR_PAIR(5));
    for (size_t i = start_index; i < end_index; ++i) {
        mvaddch(row, col + i, line[i]);
    }
    attroff(COLOR_PAIR(5));
}


void display_user_input(const std::string& user_input, const std::string& test_string, size_t start_index) {
    std::string visible_input = user_input.substr(start_index, LINE_WIDTH);

    // Clear the input line to avoid leftover characters
    mvprintw(INPUT_ROW, INPUT_COL, "%-60s", " ");

    // Display the current visible input with color coding
    for (size_t i = 0; i < visible_input.length(); ++i) {
        char input_char = visible_input[i];
        char expected_char = test_string[start_index + i];

        if (input_char == expected_char) {
            attron(COLOR_PAIR(1)); // Green
        } else {
            attron(COLOR_PAIR(2)); // Red
        }

        mvaddch(INPUT_ROW, INPUT_COL + i, input_char);
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
    }
}





void initialize_ncurses() {
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo() while we do getch
    keypad(stdscr, TRUE);   // Enable function keys and arrow keys
    curs_set(1);            // Make cursor visible (use 1 for normal visibility, 2 for highly visible)
    nodelay(stdscr, TRUE);  // Make getch() non-blocking
}

void terminate_ncurses() {
    endwin();
}

void initialize_colors() {
    if (has_colors() == FALSE) {
        terminate_ncurses();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color(); // Start color functionality

    // Define color pairs
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Correct characters
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Incorrect characters
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // User input (unused in this example)
    init_pair(4, COLOR_CYAN, COLOR_BLACK);   // Static text
    init_pair(5, COLOR_BLACK, COLOR_YELLOW); // Highlight current word (yellow background)

}

std::string get_random_test_string(const std::vector<std::string>& passages) {
    if (passages.empty()) {
        return "Default typing test string.";
    }
    int random_index = std::rand() % passages.size();
    return passages[random_index];
}

void display_timer(double remaining_time) {
    // Clear the previous timer display by overwriting with spaces
    mvprintw(11, 2, "Time Remaining: %.0f seconds    ", remaining_time);
}
