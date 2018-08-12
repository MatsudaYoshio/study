def display_inventory(inventory):
    print("item list:")
    item_total = 0
    for k, v in inventory.items():
        print(str(v) + ' ' + str(k))
        item_total = item_total+v
    print("total number: "+str(item_total))

def add_to_inventory(inventory, added_items):
    for item in added_items:
        if item in inventory.keys():
            inventory[item] = inventory[item]+1
        else:
            inventory[item] = 1

def main():
    inv = {"rope": 1, "torch": 6, "coin": 42, "throwing star": 1, "arrow": 12}
    dragon_loot = ["coin", "throwing star", "coin", "coin", "ruby"]

    add_to_inventory(inv, dragon_loot)
    
    display_inventory(inv)
    
if __name__ == '__main__':
    main()
