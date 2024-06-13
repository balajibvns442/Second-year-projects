package restaurant_management;
import java.util.ArrayList;
import java.util.Scanner ;

public class Restaurant {
    public static void main(String[] args ) {
        Scanner sc = new Scanner(System.in);
        Restaurant_system restaurantSystem = new Restaurant_order_system();

        Menu_item item1 = new Restaurant_items("BIryani", "spices from all corners ", 450);
        Menu_item item2 = new Restaurant_items("Chicken Shawarma", "get your senses reactivated", 190);
        Menu_item item3 = new Restaurant_items("Butter Chicken", "forget the world , dwell in butter", 280);
        Menu_item item4 = new Restaurant_items("uBUtter Naan", "dont forget me ", 40);

        restaurantSystem.add_to_menu(item1);
        restaurantSystem.add_to_menu(item2);
        restaurantSystem.add_to_menu(item3);
        restaurantSystem.add_to_menu(item4);

        for (Menu_item temp : restaurantSystem.get_menu()) {
            System.out.print(temp.get_ID());
            System.out.println("  name : " + temp.get_name());
            System.out.print("  price : " + temp.get_price());
            System.out.println(temp.get_description());
        }

        Order order ;
        char choice = 'y';
        int option , id , ord_id ;
        do{
            System.out.println("Welcome to HUngry puttar !");
            System.out.println(" 1 \t place new order");
            System.out.println(" 2 \t want more ?");
            System.out.println(" 3 \t on a diet , want to miss out foodgasms ?");
            System.out.println(" 4 \t get your bill , dont forget to tip ");
            System.out.println(" 5 \t have no time ? cancel order ?");

            option = sc.nextInt();
            sc.nextLine() ;

            switch (option){
                case 1 :
                    order = restaurantSystem.create_order() ;

                    System.out.println("Enter the ID of your item ");
                    id = sc.nextInt() ;
                    sc.nextLine() ;

                    if( id <= restaurantSystem.get_menu().size() ){
                        Menu_item item = restaurantSystem.get_menu().get(id-1) ;
                        order.add_item(item);
                    }
                    else
                        System.out.println("invalid option , sorry we hope taht is available next time ");

                    restaurantSystem.add_orders(order);
                    System.out.println("is there anything we can do ? [y/n]");
                    choice = sc.next().charAt(0) ;
                    break ;

                case 2 :
                    System.out.println("Enter your existing orders ID ");
                    ord_id = sc.nextInt() ;
                    sc.nextLine() ;

                    if( ord_id <= restaurantSystem.get_orders().size() ){
                        order = restaurantSystem.get_orders().get(ord_id-1) ;

                        System.out.println("Enter the ID of your item ");
                        id = sc.nextInt() ;
                        sc.nextLine() ;

                        if( id <= restaurantSystem.get_menu().size() ){
                            Menu_item item = restaurantSystem.get_menu().get(id-1) ;
                            order.add_item(item);
                        }
                        else
                            System.out.println("invalid option , sorry we hope taht is available next time ");

                        System.out.println("item added successfully");
                    }
                    else System.out.println("Invalid order , place a new order ");

                    System.out.println("is there anything we can do ? [y/n]");
                    choice = sc.next().charAt(0) ;
                    break ;

                case 3 :
                    System.out.println("Enter your existing orders ID ");
                    ord_id = sc.nextInt() ;
                    sc.nextLine() ;

                    if( ord_id <= restaurantSystem.get_orders().size() ){
                        order = restaurantSystem.get_orders().get(ord_id-1) ;

                        System.out.println("Enter the ID of your item you want to remove ");
                        id = sc.nextInt() ;
                        sc.nextLine() ;

                        if( id <= restaurantSystem.get_menu().size() ){
                            Menu_item item = restaurantSystem.get_menu().get(id-1) ;
                            order.delete_item(item);
                        }
                        else
                            System.out.println("invalid option ");

                        System.out.println("item removed successfully");
                    }
                    else System.out.println("Invalid order , place a new order ");

                    System.out.println("is there anything we can do ? [y/n]");
                    choice = sc.next().charAt(0) ;
                    break ;

                case 4 :
                    System.out.println("Enter your Order ID ");
                    ord_id = sc.nextInt() ;
                    sc.nextLine() ;

                    if( ord_id <= restaurantSystem.get_orders().size() ){
                        order = restaurantSystem.get_orders().get(ord_id-1) ;
                        for(Menu_item temp : order.get_all_items()){
                            System.out.println(temp.get_ID()+" \t"+temp.get_name()+" \t"+temp.get_price());
                        }

                        double total = order.calculate_total_bill() ;
                        System.out.println(" Your experience is worth "+total+"rupees");
                        System.out.println(" Thank you for choosing us , Visit again");
                        order.payment();

                    }
                    else System.out.println("given order doesnt exist please give a valid one \n");


                    System.out.println("is there anything we can do ? [y/n]");
                    choice = sc.next().charAt(0) ;
                    break ;

                case 5 :
                    System.out.println("Enter the ID of your order");
                    ord_id = sc.nextInt() ;
                    sc.nextLine() ;

                    if( ord_id <= restaurantSystem.get_orders().size()){
                        order = restaurantSystem.get_orders().get(ord_id-1);

                        restaurantSystem.cancel_order(order);
                        System.out.println("your order is deleted , feel free to have other items ");
                    }
                    else System.out.println("invalid order ID , please enter a valid ID ");

                    System.out.println("is there anything we can do ? [y/n]");
                    choice = sc.next().charAt(0) ;
                    break ;
            }
        }while (choice == 'y') ;

        System.out.println(" all orders ");

        for (Order temp : restaurantSystem.get_orders()){
            System.out.println("Order "+temp.get_order_ID());
            for (Menu_item item : temp.get_all_items()){
                System.out.println(item.get_ID()+" \t"+item.get_name()+" \t"+item.get_price());
            }
            System.out.println("total bill : "+temp.calculate_total_bill());
            if( !temp.status() ) System.out.println("Bill to be paid ");
            System.out.println();
        }

        sc.close();
    }
}
