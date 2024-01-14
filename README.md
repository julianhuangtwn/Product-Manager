# Product Manager
This program utilizes various OOP concepts, it manages files, which mainly
store item information that are separated into perishable and non-perishable.
Both are derived from a pure abstract class, and each objects are stored dynamically
in arrays.

Items can be manipulated, such as listing all current items, adding or removing an item, 
sort, and also a "ship item" that ships items when quantity on hand is enough

Some items which are perishable will have a Date associated with them, with the expiry date
stored in the Date objects

When there error in certain situations, the error codes and messages are stored in a 
Status object, where they usually store the actual status of the items themselves
