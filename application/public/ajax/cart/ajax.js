function addProductToCart(item_id,id_array){
    id = id_array.split(",");
    var property_array = new Array ();
    for (var i = 0; i < id.length; i++){
        property_array[i] = $('input[name="property'+id[i]+'"]:checked').val();        
    }
    property_array = property_array.join();
    $.ajax({
            type: "POST",
            url: "../../ajax/cart/additem.php",
            data: { item_id:item_id,property_array:property_array },
            cache: false,
            success: function(data){ 
                var n = data.split("/");
                alert(n[0]);                
                var t="<span style='color:#000'>В вашей корзине</span> <br/>"+n[1]+" <span style='color:#000'>товара, на сумму</span>";
                $('span[id="qty_product"]').html(t);
                $('span[id="summ_product"]').html(n[2]+" <span style='color:#000'>грн</span>");              
            }
          }); 
}
function dellProductById(item_id,id_array,cat_page){
  
    $.ajax({
            type: "POST",
            url: "../../ajax/cart/dellitem.php",
            data: { item_id:item_id,property_array:id_array },
            cache: false,
            success: function(data){               
                location.replace("http://"+$(location).attr('hostname')+"/"+cat_page); 
            }                   
    });
}
/**
 * Пересчет количества товара....
 */
function reCountProduct(items,properties,cart_page,x) {
   
    var qty_array = new Array ();
    for (var i = 0; i < x; i++){
        qty_array[i] = $('input[name="qty'+i+'"]').val();        
    }
    var qty = qty_array.join();
  
    $.ajax({
            type: "POST",
            url: "../../ajax/cart/cart.php",
            data: { items:items,property_array:properties,qty:qty },
            cache: false,
            success: function(data){ 
                location.replace("http://"+$(location).attr('hostname')+"/"+cart_page); 
            }                   
    });
}