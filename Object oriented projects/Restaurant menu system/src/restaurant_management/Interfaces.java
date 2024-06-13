package restaurant_management;

import java.util.ArrayList;
interface Menu_item {
    String get_name();
    String get_description();
    double get_price();
    int get_ID();
}

interface Order {
    int get_order_ID();
    void add_item(Menu_item name);
    void delete_item(Menu_item name) ;
    ArrayList<Menu_item> get_all_items() ;
    double calculate_total_bill() ;
    void increase_ID() ;

    void payment();
    boolean status() ;
}

interface Restaurant_system{
    Order create_order() ;
    void add_to_menu(Menu_item name) ;
    void remove_from_menu(Menu_item name) ;
    ArrayList<Menu_item> get_menu() ;
    void add_orders(Order order) ;
    ArrayList<Order> get_orders() ;
    void cancel_order(Order order) ;
}


