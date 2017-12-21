<div class="container">
    <table class="table table-striped" style="text-align: left;">
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
        <?php foreach ($transactions as $transaction): ?>
        <tr>
            <td><?= $transaction["transaction"] ?></td>
            <td><?= $transaction["time"] ?></td>
            <td><?= $transaction["symbol"] ?></td>
            <td><?= $transaction["shares"] ?></td>
            <td>$<?= format_money($transaction["price"]) ?></td>
        </tr>
        <?php endforeach ?>
    </table>
</div>
