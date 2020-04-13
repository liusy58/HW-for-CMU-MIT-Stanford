datatype tree = Oak | Elm | Maple | Spruce | Fir | 
                Pine | Willow;

datatype vegetable = Carrot | Zucchini | Tomato | 
                     Cucumber | Lettuce;

datatype grain = Wheat | Oat | Barley | Maize;

datatype plot = Grove of tree | Garden of vegetable | 
                Field of grain | Vacant;

datatype bread = White | MultiGrain | Rye | Kaiser;
datatype spread = Mayo | Mustard;
datatype vegetable = Cucumber | Lettuce | Tomato;
datatype deliMeat = Ham | Turkey | RoastBeef;
datatype noodle = Spaghetti | Penne | Fusilli | Gemelli;
datatype sauce = Pesto | Marinara | Creamy;
datatype protein = MeatBalls | Sausage | Chicken | Tofu;

datatype entree = 
     Sandwich of bread * spread * vegetable * deliMeat 
   | Pasta of noodle * sauce * protein;
datatype salad = Caesar | Garden;
datatype side = Chips | CarrotSticks | Salad of salad;
datatype beverage = Water | Coffee | Pop | Lemonade | IceTea;
datatype meal = Meal of entree * side * beverage;