<div style="width: 35%; margin: 0 auto;">
    <ul class="nav nav-pills">
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="logout.php"><strong>Log Out</strong></a></li>
    </ul>
</div>
<br />
<div class="container">
    <table class="table table-striped" style="text-align: left;">
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
        <?php foreach ($stocks as $stock): ?>
        <tr>
            <td><?= $stock["symbol"] ?></td>
            <td><?= $stock["name"] ?></td>
            <td><?= $stock["shares"] ?></td>
            <td>$<?= format_money($stock["price"]) ?></td>
            <td>$<?= format_money($stock["shares"] * $stock["price"]); ?></td>
        </tr>
        <?php endforeach ?>
        <tr>
            <td colspan="4">CASH</td>
            <td>$<?= format_money($cash) ?></td>
        </tr>
    </table>
</div>
<a href="account.php">Change Password</a>
