package restaurant_management;

import java.util.ArrayList;

class Restaurant_items implements Menu_item {
    private static int next_ID = 1 ;
    private int item_ID ;
    private String name ;
    private String description ;
    private double price ;

    public Restaurant_items(String name , String description , double price ){
        item_ID = next_ID ;
        next_ID++ ;
        this.name = name ;
        this.description = description ;
        this.price = price ;
    }

    @Override
    public int get_ID() {
        return item_ID;
    }
    public String get_name() {
        return name;
    }
    public String get_description() {
        return description;
    }

    public double get_price() {
        return price;
    }
}

class Restaurant_orders implements Order {
    private static int next_ID = 1;
    private int order_ID;
    private ArrayList<Menu_item> items;
    private boolean paid;

    public Restaurant_orders() {
        items = new ArrayList<Menu_item>();
        this.order_ID = next_ID;
        this.paid = false;
    }

    public int get_order_ID() {
        return order_ID;
    }

    public ArrayList<Menu_item> get_all_items() {
        return items;
    }

    public void add_item(Menu_item name) {
        this.items.add(name);
    }

    @Override
    public void delete_item(Menu_item name) {
        this.items.remove(name);
    }

    public double calculate_total_bill() {
        double sum = 0;
        for (Menu_item temp : this.items)
            sum += temp.get_price();
        return sum;
    }

    public void increase_ID() {
        next_ID++;
    }

    @Override
    public void payment() {
        this.paid = true ;
    }

    @Override
    public boolean status() {
        return this.paid;
    }
}
class Restaurant_order_system implements Restaurant_system{
    private ArrayList<Menu_item> Menu ;
    private ArrayList<Order> orders ;

    public Restaurant_order_system(){
        this.Menu = new ArrayList<Menu_item>();
        this.orders = new ArrayList<Order>();
    }
    public void add_to_menu(Menu_item name){
        this.Menu.add(name);
    }
    public void remove_from_menu(Menu_item name){
        this.Menu.remove(name);
    }

    public Order create_order(){
        Order order = new Restaurant_orders();
        order.increase_ID();
        return order ;
    }
    public ArrayList<Menu_item> get_menu(){
        return this.Menu ;
    }
    public void add_orders(Order order){
        this.orders.add(order);
    }
    public ArrayList<Order> get_orders(){
        return this.orders ;
    }
    public void cancel_order(Order order){
        this.orders.remove(order);
    }
}