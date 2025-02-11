package view;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MenuView extends JFrame {

    private static final long serialVersionUID = 9199955804186317264L;

    public MenuView() {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100, 100, 450, 300);
        JPanel contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        contentPane.setLayout(new GridLayout(3, 1, 10, 10)); // 3 rows, 1 column, 10px vertical gap

        contentPane.add(createButton("Categoria", this::openCategoriaView));
        contentPane.add(createButton("Item", this::openItemView));
        contentPane.add(createButton("Tipo Acomodação", this::openTipoAcomodacaoView));
        contentPane.add(createButton("Acomodação", this::openAcomodacaoView));
        contentPane.add(createButton("Hospede", this::openHospedeView));
        contentPane.add(createButton("Hospedagem", this::openHospedagemView));
        contentPane.add(createButton("Conta", this::openContaView));
        contentPane.add(createButton("Pagamento", this::openPagamentoView));

        setContentPane(contentPane);
    }

    private JButton createButton(String text, ActionListener actionListener) {
        JButton button = new JButton(text);
        button.addActionListener(actionListener);
        return button;
    }

    private void openCategoriaView(ActionEvent e) {
        CategoriaView categoriaView = new CategoriaView();
        categoriaView.setVisible(true);
    }

    private void openItemView(ActionEvent e) {
        ItemView itemView = new ItemView();
        itemView.setVisible(true);
    }

    private void openTipoAcomodacaoView(ActionEvent e) {
        TipoAcomodacaoView tipoAcomodacaoView = new TipoAcomodacaoView();
        tipoAcomodacaoView.setVisible(true);
    }

    private void openAcomodacaoView(ActionEvent e) {
        AcomodacaoView acomodacaoView = new AcomodacaoView();
        acomodacaoView.setVisible(true);
    }

    private void openHospedeView(ActionEvent e) {
        HospedeView hospedeView = new HospedeView();
        hospedeView.setVisible(true);
    }

    private void openHospedagemView(ActionEvent e) {
        HospedagemView hospedagemView = new HospedagemView();
        hospedagemView.setVisible(true);
    }

    private void openContaView(ActionEvent e) {
        ContaView contaView = new ContaView();
        contaView.setVisible(true);
    }

    private void openPagamentoView(ActionEvent e) {
        PagamentoView pagamentoView = new PagamentoView();
        pagamentoView.setVisible(true);
    }
}