#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("Matus Bursa <burso@burso.eu>");
MODULE_DESCRIPTION("rofl - generating jokes to /dev/rofl");
MODULE_LICENSE("Beerware");
MODULE_VERSION("0.1.0");

#define MAX_SIZE 1024

static ssize_t rofl_read(struct file *, char *, size_t, loff_t *);

static const char rofl_jokes[][MAX_SIZE] = { 
	"I dreamt I was forced to eat a giant marshmallow. When I woke up, my pillow was gone.\n",
	"My dog used to chase people on a bike a lot. It got so bad, finally I had to take his bike away.\n",
	"It is so cold outside I saw a politician with his hands in his own pockets.\n",
	"What's the difference between snowmen and snowladies? Snowballs \n",
	"Why did the blonde get excited after finishing her puzzle in 6 months? -- The box said 2-4 years!\n",
	"I am a nobody, nobody is perfect, therefore I am perfect.\n",
	"My mom never saw the irony in calling me a son-of-a-bitch.\n",
	"I used to like my neighbors, until they put a password on their Wi-Fi.\n",
	"Stalking is when two people go for a long romantic walk together but only one of them knows about it.\n",
	"How do you seduce a fat woman? Piece of cake.\n",
	"What do you call a blonde with a brain? A golden retriever.\n",
	"How do you make a tissue dance? You put a little boogie in it.",
	"Why did the policeman smell bad? He was on duty.",
	"Why does Snoop Dogg carry an umbrella? FO DRIZZLE!",
	"Why can’t you hear a pterodactyl in the bathroom? Because it has a silent pee.",
	"What did the Zen Buddist say to the hotdog vendor? Make me one with everything.",
	"What kind of bees make milk instead of honey? Boobies.",
	"Horse walks into a bar. Bartender says, “Why the long face?”",
	"A mushroom walks into a bar. The bartender says, “Hey, get out of here! We don’t serve mushrooms here”. Mushroom says, “why not? I’m a fungai!”",
	"I never make mistakes…I thought I did once; but I was wrong.",
	"What’s Beethoven’s favorite fruit?…Ba-na-na-naaa!",
	"What did the little fish say when he swam into a wall? DAM!",
	"Knock knock. Who’s there? Smell mop. (finish this joke in your head)",
	"Where does a sheep go for a haircut? To the baaaaa baaaaa shop!",
	"What does a nosey pepper do? Gets jalapeno business!",
	"What do you call a deer with no eyes? No eye deer.",
	"What’s the last thing that goes thru a bug’s mind as he hits the windshield? His butt.",
	"Knock knock- who’s there? Dwayne. Dwayne who? Dwayne the tub I’m dwounding!",
	"The past, present and future walk into a bar. It was tense.",
	"What goes “ha ha thump”? A man laughing his head off.",
	"What did the grape say when he was pinched? Nothing, he gave a little wine.",
	"What’s brown and sticky? A stick!",
	"Why are pirates so mean? I don’t know, they just arrrrrrrrr!",
	"Why was Tigger looking in the toilet? He was looking for Pooh!",
	"What do you get when you throw a piano down a mine shaft? A flat miner.",
	"Have you heard about the cannibal that passed his brother in the forest?",
	"Who’s there?” … “Control freak. Okay now you say, ‘Control freak who?”",
	"What do you call cheese that’s not yours? It’s nacho cheese.",
	"What do you get when you put a candle in a suit of armor? A knight light.",
	"Have you heard about corduroy pillows?! They’re making headlines!",
	"Two drums and a cymbal fall off a cliff. Ba-dum Tish!",
	"There were two peanuts walking down a dark alley, one was assaulted.",
	"What do you call a sleepwalking nun… A roamin’ Catholic.",
	"How do you make holy water? You boil the hell out of it.",
	"What did the 0 say to the 8? Nice belt!",
	"Why did the orange stop? Because, it ran outta juice.",
	"What’s brown and sounds like a bell? Dung!",
	"Knock knock. Who’s there? Interrupting Cow. Interrupting Cow wh- MOOOOOOO!",
	"Why did the storm trooper buy an iphone? He couldn’t find the Droid he was looking for.",
	"Knock knock…who’s there? I eat mop. I eat mop who? Ooooo gross! (now do you get the earlier one?)",
	"Why is six afraid of seven? Because seven ate nine.",
	"Why did the stop light turn red??? You would too if you had to change in the middle if the street!",
	"Bacon and eggs walk into a bar and order a beer, the bartender says sorry, we don’t serve breakfast.",
	"What do you do with a dead chemist …. You Barium.",
	"What’s the difference between a woman with PMS and a Pitt Bull? – Lipstick!",
	"A guy walks into a bar with a set of jumper cables…the bartender says, buddy, I’ll serve you as long as you don’t start anything.",
	"Two cows are sitting in a field, and one says to the other, “so, how about that mad cow disease? Scary stuff, right?” To which to other replies, “terrifying. But what do I care? I’m a helicopter.”",
	"How does Jesus make tea???? Hebrews it.",
	"What do you get when you cross an elephant and a rhino? Elephino!",
	"What did the farmer say when he couldn’t find his tractor? “Where’s my Tractor?!”",
	"Have you heard about the duck that was arrested for dealing? He was selling “quack”.",
	"What do you call a cow with two legs? Lean beef.",
	"How do you catch a unique rabbit? You ‘neek’ up on it.",
	"How do you catch a tame rabbit? The ‘tame’ way.",
	"What did the green grape say to the purple grape? BREATHE!",
	"*While waving your hands on either side of the other person’s head* “running through the woods, running through the woods, running through the woods. Close our eyes!” *smack person on forehead* “TREE! Never close your eyes when you’re running through the woods!”",
	"Knock, knock. Who’s there? Hippa. Hippa who? I’m sorry, I’can’t tell you that.",
	"Two muffins are in an oven. One muffin says “gosh, it’s hot in here”. The other muffin screams “AAAH!! A talking muffin!”",
	"If you’re American in the living room, what are you in the bathroom? European!",
	"A liberal, a moderate, and a conservative walk into a bar. Bartender says, “Hey Mitt! What’ll ya have?”",
	"What does the man in the moon do when his hair gets too long? Eclipse it!",
	"ate walks into a bar with a ship’s steering wheel hanging from his crotch. Bartender says, what the hell is that? Pirate says, I dunno, but it’s drivin’ me nuts!",
	"What’s the difference between a straight woman and a bisexual woman? 4 drinks.",
	"How do you make a hormone? Don’t pay her!",
	"What’s the hardest part of a vegetable to eat? The wheelchair.",
	"Why did the blonde get fired from the M&M factory? Because she threw away all the ‘w’s!",
	"What’s green and smells like pork? Kermit’s fingers.",
	"What do men and tile have in common? If you lay them right the first time you can walk all over them the rest of your life!",
	"How many flies does it take to screw in a light bulb? Two…. but I don’t know how they got in there.",
	"Why did the blonde have a sore belly button? Because there are blonde men too!",
	"Where does a bee keep his stinger? In his honey!",
	"A dyslexic man walks into a bra.",
	"How many Alzheimer’s patients does it take to change a light bulb?….. To get to the other side!",
	"What do you call a masturbating cow? Beef stroganoff.",
	"What do you have when you have two little green balls in the palm of your hand?? Answer: Kermit’s undivided attention!",
	"What did one snowman say to the other? Nice balls.",
	"What do you get when you cross an insomniac, an agnostic and a dyslexic? Someone who lays awake at night wondering if there really is a dog.",
	"I used to date a dyslexic woman. I took her home and she ended up cooking my sock.",
	"What did one tampon say to the other tampon? Nothing! They were both stuck up bitches.",
	"A bowlegged doe comes walking out of the woods. Says “that’s the last time I do that for ten bucks”",
	"I used to be into sadism, necrophilia, and bestiality, but I realized I was just beating a dead horse.",
	"Confucius says, when naked man walk through doorway sideways, he going to Bangkok.",
	"Why did the walrus go to the Tupperware party? He was looking for a tight seal!",
	"3 old ladies in a park. A man walks up and opens his trench to reveal his naked self … The first old lady has a stroke and the second old lady has a stroke. The third one can’t cause her arm isn’t long enough.",
};

static const struct file_operations rofl_fops = {
        .owner = THIS_MODULE,
        .read  = rofl_read,
};

static struct miscdevice rofl_dev = {      
        MISC_DYNAMIC_MINOR,     
        "rofl",
        &rofl_fops
};

static ssize_t rofl_read(struct file * file, char * buffer, 
                          size_t count, loff_t *ppos)
{
	int i, random_number;

	get_random_bytes(&i, sizeof(i));	
	random_number = i % (sizeof(rofl_jokes) / MAX_SIZE);
    
    size_t len = strlen(rofl_jokes[random_number]); 
    if (count < len)
		return -EINVAL;
    
    if (*ppos != 0)
        return 0;
    
    if (copy_to_user(buffer, rofl_jokes[random_number], len))
        return -EINVAL;
    
    *ppos = len;
    return len;
}

static int __init rofl_init(void)
{
        int ret = 0;   
        ret = misc_register(&rofl_dev);
        if (ret) {
                printk(KERN_ERR "Unable to register \"/dev/rofl\" device\n");
		}

        return ret;
}

static void __exit rofl_exit(void)
{
        misc_deregister(&rofl_dev);
}

module_init(rofl_init);
module_exit(rofl_exit);
